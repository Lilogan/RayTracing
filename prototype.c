color determineColor(*listObj headListObject, *list ){
  listObj *currentListObject = headListObject
  float distanceMin;
  void *closestObject;
  while(currentListObject != NULL){
    int distance;
    int currentObject = &(currentObject->elt);
    // distance = calcul distance
    if(distanceMin < distance){
      distanceMin = distance;
      closestObject = currentObject;
    }
    currentListObject = currentListObject->next;
  }

  if(closestObject != NULL){
    point pos = intersectHalfLine(closestObject)
    color detColor = "colorFond"


  }
}
