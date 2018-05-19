#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "geometric3DTools.h"
#include "object.h"

#define MAXFLOAT 99999999999
#define DEFCOLOR setColor(0,0,0)
#define OMBERCOLOR setColor(0,255,0)



color getLight(object light, object obj, vector intersect, point intersectPoint){
  vector normal = normalObject(obj,intersectPoint);
  double angle = acos(cosVector(normal,intersect));
  if(1/*angle <= M_PI_2*/){
    color oColor = obj.oMaterial.oColor;
    color lColor = light.oMaterial.oColor;
    color result = timesColor(oColor,lColor);
    //result = timesColorNumber(result,angle);
    return result;
  }else{
    return OMBERCOLOR;
  }
}

color determineColor(listObj* headListObject, listObj* headListLight, point camera, point currentPixel){
  listObj *currentListObject = headListObject;
  listObj *currentListLight = headListLight;
  float distanceMin = MAXFLOAT;
  object *closestObject = NULL;
  color detColor = DEFCOLOR;

  while(currentListObject != NULL){
    object currentObject = currentListObject->elt;
    halfLine currentHalfLine = setHalfLine(camera, currentPixel);
    point* currentIntersect = intersectHalfLine(currentObject, currentHalfLine, camera);
    float currentDistance;

    if(currentIntersect != NULL){
      if(closestObject == NULL){
        closestObject = malloc(sizeof(object));
      }
      currentDistance = distancePoints(currentPixel, *currentIntersect);
    }else{
      currentDistance = MAXFLOAT;
    }

    if(distanceMin > currentDistance){
      distanceMin = currentDistance;
      *closestObject = currentObject;
    }
    currentListObject = currentListObject->next;
  }

  if(closestObject != NULL){
    while (currentListLight != NULL) {
      bool lampIsClosest = true;
      object currentLight = currentListLight->elt;
      point currentLightPoint = currentLight.parameter.pt;
      halfLine hlCameraPixel = setHalfLine(camera,currentPixel);
      point *firstIntersect = intersectHalfLine(*closestObject, hlCameraPixel, camera);;
      halfLine hlLampFirstIntersect = setHalfLine(currentLightPoint, *firstIntersect);
      currentListObject = headListObject;

      while(currentListObject != NULL && lampIsClosest){
        object currentObject = currentListObject->elt;
        int distanceFirstIntersectLamp = (int)distancePoints(currentLightPoint, *firstIntersect);
        point *secondIntersect = intersectHalfLine(currentObject, hlLampFirstIntersect, currentLightPoint);
        int distanceSecondIntersectLamp = -1;

        if(secondIntersect != NULL && closestObject->id != currentObject.id){
          distanceSecondIntersectLamp = (int)distancePoints(currentLightPoint, *secondIntersect);
        }

        if(distanceSecondIntersectLamp < distanceFirstIntersectLamp && distanceSecondIntersectLamp != -1){
          lampIsClosest = false;
        }
        currentListObject = currentListObject->next;
      }

      if(lampIsClosest){
        color calc =  getLight(currentLight,*closestObject,hlLampFirstIntersect.dir,*firstIntersect);
        detColor = addColor(detColor,calc);
      }
      currentListLight = currentListLight->next;
    }
  }
  free(closestObject);
  return detColor;
}



int main() {
  int width = 1000;
  int height = 1000;
  int distanceCameraEcran = -500;
  int distanceSpheroideEcran = 750;
  int rayonSpheroide = 200;

  image* I = newImage(width, height);
  point camera = setPoint(width/2, distanceCameraEcran, height/2);
  spheroide sp = setSpheroide(1, 1, 1, 0, 0, 0, 0, 0, 0, pow(rayonSpheroide, 2), width/4,  distanceSpheroideEcran, rayonSpheroide);
  spheroide sp2 = setSpheroide(1, 1, 1, 0, 0, 0, 0, 0, 0, pow(rayonSpheroide, 2), 3*width/4,  distanceSpheroideEcran, rayonSpheroide);
  point lamp = setPoint(width, 2, height);
  point lamp2 = setPoint(0,2,height);


  cartesianPlan sol;
  sol.a = 0;
  sol.b = 0;
  sol.c = 1;
  sol.d = 0;

  material matLamp = createMaterial(setColor(255,0,0),0,0,0);
  material matLamp2 = createMaterial(setColor(0,0,255),0,0,0);
  material matSp = createMaterial(setColor(255,255,255),0,0,0);
  material matSol = createMaterial(setColor(144,144,144),0,0,0);

  object oSp = createObjectSpheroide(sp,matSp);
  object oSp2 = createObjectSpheroide(sp2,matSp);
  object oLamp = createObjectPoint(lamp,matLamp);
  object oLamp2 = createObjectPoint(lamp2,matLamp2);
  object oSol = createObjectPlan(sol, matSol);


  listObj *listLamp = createElt(oLamp);
  addObjToList(listLamp,oLamp2);
  listObj *objects = createElt(oSp);
  addObjToList(objects,oSp2);
  addObjToList(objects,oSol);

  color a = timesColor(oSol.oMaterial.oColor,oLamp.oMaterial.oColor);

  for(int i = 0; i<width; i++){
    for(int j = 0; j<height; j++){
      color colorPixel = determineColor(objects, listLamp, camera, setPoint(i,0,j));
      setPixel(I,i,height-j,colorPixel);
    }
  }
  printf("\n");
  save(I,"test2.bmp");

  return 0;
}
