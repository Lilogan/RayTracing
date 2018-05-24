#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "geometric3DTools.h"
#include "object.h"

#define MAXFLOAT 9999999999999
#define DEFCOLOR setColor(0,0,0)



color getLight(object light, object obj, halfLine intersect, point intersectPoint, point camera){
  vector normal = normalObject(obj,intersectPoint, intersect, camera);
  double angle = cosVector(normal,intersect.dir);
  color fColor = DEFCOLOR;
  color oColor = obj.oMaterial.oColor;
  color lColor = light.oMaterial.oColor;
  color aColor = timesColor(oColor,lColor);
  if(angle > 0){
    fColor = timesColorNumber(aColor,angle);
  }
  //color result = addColor(fColor,timesColorNumber(aColor,0.2));
  return fColor;
}

color determineColor(listObj* headListObject, listObj* headListLight, point camera, point currentPixel){
  listObj *currentListObject = headListObject;
  listObj *currentListLight = headListLight;
  float distanceMin = -1;
  object* closestObject = NULL;
  point point1 = camera;
  point point2 = currentPixel;
  color detColor = DEFCOLOR;
  bool isReflected = true;
  halfLine currentHalfLine;
  point* currentIntersect;
  int previousClosestObjectId = -1;

  while(isReflected == true){
    if(closestObject != NULL){
      free(closestObject);
      closestObject = NULL;
    }
    currentListObject = headListObject;
    currentHalfLine = setHalfLine(point1, point2);
    isReflected = false;
    while(currentListObject != NULL){
      object currentObject = currentListObject->elt;
      currentIntersect = intersectHalfLine(currentObject, currentHalfLine, point1);
      float currentDistance;
      if(currentIntersect != NULL){
        if(closestObject == NULL){
          closestObject = (object*)malloc(sizeof(object));
        }
        currentDistance = distancePoints(point2, *currentIntersect);
      }else{
        currentDistance = -1;
      }
      if((distanceMin > currentDistance && currentDistance != -1) || (distanceMin == -1 && currentDistance != -1)){

        distanceMin = currentDistance;
        *closestObject = currentObject;

      }
      currentListObject = currentListObject->next;
    }

  /*  if(closestObject != NULL){
      if(closestObject->oMaterial.reflect != 0 && (closestObject->id != previousClosestObjectId || previousClosestObjectId == -1)){
        previousClosestObjectId = closestObject->id;
        vector refractedVector = reflectObject(*closestObject, currentHalfLine);
        printf("%f %f %f\n",refractedVector.x,refractedVector.y, refractedVector.z);
        if(refractedVector.x != 0 || refractedVector.y !=0 || refractedVector.z != 0){
          isReflected = true;
          point2 = translate(*currentIntersect, refractedVector);
          printf("%f %f %f\n", point2.x, point2.y, point2.z);
          point1 = *currentIntersect;
          printf("%f %f %f\n", point1.x, point1.y, point1.z);
        }
      }
    }*/

  }

  if(closestObject != NULL){
    while (currentListLight != NULL) {
      bool lampIsClosest = true;
      currentHalfLine = setHalfLine(point1, point2);
      object currentLight = currentListLight->elt;
      point currentLightPoint = currentLight.parameter.pt;
      halfLine hlCameraPixel = setHalfLine(point1,point2);
      point *firstIntersect = intersectHalfLine(*closestObject, hlCameraPixel, point1);
      halfLine hlLampFirstIntersect = setHalfLine(*firstIntersect,currentLightPoint);
      currentListObject = headListObject;

      while(currentListObject != NULL && lampIsClosest){
        object currentObject = currentListObject->elt;
        float distanceFirstIntersectLamp = distancePoints(currentLightPoint, *firstIntersect);
        point *secondIntersect = intersectHalfLine(currentObject, hlLampFirstIntersect, currentLightPoint);
        float distanceSecondIntersectLamp = -1;

        if(secondIntersect != NULL && closestObject->id != currentObject.id){
          distanceSecondIntersectLamp = distancePoints(currentLightPoint, *secondIntersect);
        }

        if(distanceSecondIntersectLamp < distanceFirstIntersectLamp && distanceSecondIntersectLamp != -1){
          lampIsClosest = false;
        }
        currentListObject = currentListObject->next;
      }

      if(lampIsClosest){
        color calc =  getLight(currentLight,*closestObject,hlLampFirstIntersect,*firstIntersect,camera);
        detColor = addColor(detColor,calc);
      }
      currentListLight = currentListLight->next;
    }
    free(closestObject);
  }
  return detColor;
}



int main() {
  int width = 1000;
  int height = 1000;
  int distanceCameraEcran = -500;
//  int distanceSpheroideEcran = 600;
//  int rayonSpheroide = 300;

  image* I = newImage(width, height);
  point camera = setPoint(width/2, distanceCameraEcran, height/2);

  listObj *listLamp = NULL;
  listObj *objects = NULL;
  FILE* file = fopen("../allInfos","r");
  fseek(file, 0, 0);
  char curInfo[7];

  while(fgets(curInfo,7,file)){
    if(strncmp(curInfo, "LAMPE",5) == 0){
      point lampePos;
      material lampeMat;
      object newLampe;
      int red;
      int green;
      int blue;

      //set lampe position
      fgets(curInfo,7,file);
      lampePos.x = atof(curInfo);
      fgets(curInfo,7,file);
      lampePos.y = atof(curInfo);
      fgets(curInfo,7,file);
      lampePos.z = atof(curInfo);


      //set lampe colorPixel
      fgets(curInfo,7,file);
      red= atoi(curInfo);
      fgets(curInfo,7,file);
      green= atoi(curInfo);
      fgets(curInfo,7,file);
      blue= atoi(curInfo);

      //set lampe material
      lampeMat = createMaterial(setColor(red,green,blue),0,0,0);

      //set lampeMat
      newLampe = createObjectPoint(lampePos, lampeMat);

      //save the lampeMat
      if(listLamp == NULL){
        listLamp = createElt(newLampe);
      }else{
        addObjToList(listLamp, newLampe);
      }
    }
    else if(strncmp(curInfo, "PLAN",4) == 0){
      cartesianPlan plan;
      material planMat;
      object newPlan;
      int red;
      int green;
      int blue;
      float reflection;
      float transparency;
      float refraction;

      //set lampe position
      fgets(curInfo,7,file);
      plan.a = atof(curInfo);
      fgets(curInfo,7,file);
      plan.b = atof(curInfo);
      fgets(curInfo,7,file);
      plan.c = atof(curInfo);
      fgets(curInfo,7,file);
      plan.d = atof(curInfo);


      //set plan colorPixel
      fgets(curInfo,7,file);
      red= atoi(curInfo);
      fgets(curInfo,7,file);
      green= atoi(curInfo);
      fgets(curInfo,7,file);
      blue= atoi(curInfo);
      fgets(curInfo,7,file);
      reflection= atof(curInfo);
      fgets(curInfo,7,file);
      transparency = atof(curInfo);
      fgets(curInfo,7,file);
      refraction= atof(curInfo);

      //set plan material
      planMat = createMaterial(setColor(red,green,blue),reflection,transparency,refraction);

      //set lampeMat
      newPlan = createObjectPlan(plan, planMat);

      //save the lampeMat
      if(objects == NULL){
        objects = createElt(newPlan);
      }else{
        addObjToList(objects, newPlan);
      }
    }
    else if(strncmp(curInfo, "SP",2) == 0){
      spheroide sp;
      material spMat;
      object newSp;
      float rayonA;
      float rayonB;
      float rayonC;
      float centreX;
      float centreY;
      float centreZ;

      int red;
      int green;
      int blue;
      float reflection;
      float transparency;
      float refraction;

      //set lampe position
      fgets(curInfo,7,file);
      rayonA = atof(curInfo);
      fgets(curInfo,7,file);
      rayonB = pow(rayonA/atof(curInfo),2);
      fgets(curInfo,7,file);
      rayonC = pow(rayonA/atof(curInfo),2);

      fgets(curInfo,7,file);
      centreX = atof(curInfo);
      fgets(curInfo,7,file);
      centreY = atof(curInfo);
      fgets(curInfo,7,file);
      centreZ = atof(curInfo);


      //set lampe colorPixel
      fgets(curInfo,7,file);
      red= atoi(curInfo);
      fgets(curInfo,7,file);
      green= atoi(curInfo);
      fgets(curInfo,7,file);
      blue= atoi(curInfo);
      fgets(curInfo,7,file);
      reflection= atof(curInfo);
      fgets(curInfo,7,file);
      transparency = atof(curInfo);
      fgets(curInfo,7,file);
      refraction= atof(curInfo);


      //set rayonSpheroide
      sp = setSpheroide(1,rayonB,rayonC,0,0,0,0,0,0,pow(rayonA,2),centreX,centreY,centreZ);

      //set lampe material
      spMat = createMaterial(setColor(red,green,blue),reflection,transparency,refraction);

      //set lampeMat
      newSp = createObjectSpheroide(sp, spMat);

      //save the lampeMat
      if(objects == NULL){
        objects = createElt(newSp);
      }else{
        addObjToList(objects, newSp);
      }
    }
    else if(strncmp(curInfo, "SO", 2) == 0){
    //  printf("add Solid\n");
      fgets(curInfo,7,file);
      int nbrFace = atoi(curInfo);
  //    printf("Nb Face : %d\n",nbrFace);
      int nbSommets;
      float x;
      float y;
      float z;

      int red;
      int green;
      int blue;
      float reflection;
      float transparency;
      float refraction;

      solid so;
      material soMat;
      object newSo;

      so.nbPolygon = nbrFace;
      polygon *tabPolygon = malloc(nbrFace*sizeof(polygon));

      for(int i = 0; i < nbrFace; i++){
        fgets(curInfo,7,file);
        nbSommets = atoi(curInfo);
        polygon poly;
        poly.pointNbr = nbSommets;
      //  printf("nbSommets : %d\n", nbSommets);
        point *sommets = malloc(nbSommets*sizeof(point));

        for(int j = 0; j<nbSommets;j++){
          fgets(curInfo, 7, file);
          x = atof(curInfo);
          fgets(curInfo, 7, file);
          y = atof(curInfo);
          fgets(curInfo, 7, file);
          z = atof(curInfo);
          sommets[j] = setPoint(x,y,z);
        }
        poly.vertex = sommets;
        tabPolygon[i] = poly;
      }
      so.tabPolygon = tabPolygon;

      fgets(curInfo,7,file);
      red= atoi(curInfo);
      fgets(curInfo,7,file);
      green= atoi(curInfo);
      fgets(curInfo,7,file);
      blue= atoi(curInfo);
      fgets(curInfo,7,file);
      transparency= atof(curInfo);
      fgets(curInfo,7,file);
      reflection = atof(curInfo);
      fgets(curInfo,7,file);
      refraction= atof(curInfo);

      //set lampe material
      soMat = createMaterial(setColor(red,green,blue),reflection,transparency,refraction);

      //set lampeMat
      newSo = createObjectSolid(so, soMat);
      //save the lampeMat
      if(objects == NULL){
        objects = createElt(newSo);
      }else{
        addObjToList(objects, newSo);
      }
    }
  }
  for(int i = 0; i<width; i++){
    for(int j = 0; j<height; j++){
      //printf("%d-%d\n",i,j);
      color colorPixel = determineColor(objects, listLamp, camera, setPoint(i,0,j));
      setPixel(I,i,height-j,colorPixel);
    }
  }
  printf("\n");
  save(I,"test2.bmp");

  return 0;
}
