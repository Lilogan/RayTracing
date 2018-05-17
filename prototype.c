#define DEFCOLOR setPixel(0,0,0)

color getLight(object light, object obj, vector intersect){


}

color determineColor(*listObj headListObject, *listOBj headListLight, point camera, point currentPixel){
  listObj *currentListObject = headListObject;
  listObj *currentListLight = headListLight;
  float distanceMin = 9999999;
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
      currentDistance = 999999;
    }

    if(distanceMin > distance){
      distanceMin = distance;
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
        halfLine hlLampFirstIntersect = setHalfLine(currentLightPoint, &firstIntersect);
        point *secondIntersect = intersectHalfLine(currentObject, hlLampFirstIntersect, lamp);

        if(secondIntersect == NULL){
          detColor = /*calcul Light*/
        }else{
          detColor = /*ombre*/
        }


        currentListObject = currentListObject->next;
      }
      currentListObject = currentListObject->next;
    }
  }
  return detColor;
}
