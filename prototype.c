color determineColor(*listObj headListObject, *listOBj headListLight, point camera, point currentPixel){
  listObj *currentListObject = headListObject;
  listObj *currentListLight = headListLight;
  float distanceMin = 99999;
  void *closestObject;
  color detColor = "colorFond";

  while(currentListObject != NULL){
    int distance;
    object currentObject = &(currentListObject->elt);
    distance = /*calcul distance*/

    if(distanceMin > distance){
      distanceMin = distance;
      closestObject = currentObject;
    }
    currentListObject = currentListObject->next;
  }

  if(closestObject != NULL){
    halfLine hlCameraPixel = setHalfLine(camera, currentPixel);
    point *firstIntersect = intersectHalfLine(closestObject, hlCameraPixel, camera)

    while (currentListLight != NULL) {
      object currentLight = &(currentListLight->elt);
      point currentLightPoint = &(currentLight->parameter);
      currentListObject = headListObject;

      while(currentListObject != NULL){
        object currentObject = &(currentListObject->elt);
        halfLine hlLampFirstIntersect = setHalfLine(currentLightPoint, &firstIntersect);
        point *secondIntersect = intersectHalfLine(currentObject, hlLampFirstIntersect, lamp);

        if(secondIntersect != NULL){
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
