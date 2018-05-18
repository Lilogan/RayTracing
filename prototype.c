#define DEFCOLOR setColor(0,0,0)
#define OMBERCOLOR setColor(50,50,50)
#include "bmp.h"
#include "object.h"
#include "geometric3DTools.h"
#include <math.h>

color getLight(object light, object obj, vector intersect){
  vertor normal = normalObject(obj);
  normal = normalizeVector(normal);
  intersect = normalizeVector(intersect);
  double angle = acos(cosVector(normal,intersect));
  if(angle <= M_PI_2){
    color oColor = obj.oMaterial.oColor;
    color lColor = light.oMaterial.oColor;
    color result = timesColor(oColor,lColor);
    color result = timesColorNumber(result,angle);
    return result;
  }else{
    return setColor(0,0,0);
  }
}

color determineColor(*listObj headListObject, *listOBj headListLight, point camera, point currentPixel){
  listObj *currentListObject = headListObject;
  listObj *currentListLight = headListLight;
  float distanceMin = MAXFLOAT;
  void *closestObject;
  color detColor = DEFCOLOR;

  while(currentListObject != NULL){
    object currentObject = &(currentListObject->elt);
    halfLine currentHalfLine = setHalfLine(camera, currentPixel);
    point* currentIntersect = intersectHalfLine(closestObject, currentHalfLine, camera);
    float currentDistance;

    if(currentIntersect != NULL){
      currentDistance = distancePoints(currentPixel, &currentIntersect);
    }else{
      currentDistance = MAXFLOAT;
    }

    if(distanceMin > currentDistance){
      distanceMin = currentDistance;
      closestObject = currentObject;
    }
    currentListObject = currentListObject->next;
  }

  if(closestObject != NULL){
    halfLine hlCameraPixel = setHalfLine(camera, currentPixel);
    point *firstIntersect = intersectHalfLine(closestObject, hlCameraPixel, camera);

    while (currentListLight != NULL) {
      object currentLight = &(currentListLight->elt);
      point currentLightPoint = &(currentLight->parameter);
      currentListObject = headListObject;

      while(currentListObject != NULL){
        object currentObject = &(currentListObject->elt);

        if(currentObject != closestObject){
          halfLine hlLampFirstIntersect = setHalfLine(currentLightPoint, &firstIntersect);
          point *secondIntersect = intersectHalfLine(currentObject, hlLampFirstIntersect, lamp);

          if(secondIntersect == NULL){
            detColor = getLight(currentLight,closestObject, hlLampFirstIntersect.dir);
          }else{
            detColor = OMBERCOLOR;
          }
        }
        currentListObject = currentListObject->next;
      }
      currentListObject = currentListObject->next;
    }
  }
  return detColor;
}
