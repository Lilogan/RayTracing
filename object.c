#include "object.h"

material createMaterial(color oColor, float reflect, float transparency, float refraction){
  material mat;
  mat.oColor = oColor;
  mat.reflect = reflect
  mat.transparency = transparency;
  mat.refraction = refraction
  return mat;
}

object createObject(char *type , void *parameter, material oMaterial){
  object obj;
  obj.type = type;
  obj.parameter = parameter;
  obj.oMaterial = oMaterial;
  return obj;
}

point *intersectHalfLine(object obj, halfLine ray, point pointDistance){
  point *intersection;
  if(!strcmp(obj.type,"SP")){
     spheroide *sp = (spheroide)obj.parameter;
    intersection = intersectSpheroideHalfLine(*sp,ray,pointDistance);
    return intersection;
  }
  if(!strcmp(obj.type,"PL")){
    parametricPlan *pl = (parametricPlan)obj.parameter;
    intersection = intersectPlanHalfLine(*pl,ray);
    return intersection;
  }
  if(!strcmp(obj.type,"SO")){
    polygon *so = (solid)obj.parameter;
    intersection = intersectSolidHalfLine(*po,ray);
    return intersection;
  }
  if(!strcmp(obj.type,"PT")){
    return NULL;
  }
}

vector normalObject(object obj, point normalPoint){
  vector normal;
  if(!strcmp(obj.type,"SP")){
     spheroide *sp = (spheroide)obj.parameter;
    normal = normalSpheroide(*sp,normalPoint);
    return normal;
  }
  if(!strcmp(obj.type,"PL")){
     parametricPlan *pl = (parametricPlan)obj.parameter;
    normal = normalPlan(*pl,normalPoint);
    return normal;
  }
  if(!strcmp(obj.type,"SO")){
     solid *so = (solid)obj.parameter;
    normal = normalSolid(*so,normalPoint);
    return normal;
  }
  if(!strcmp(obj.type,"PT")){
    return setVector(setPoint(0,0,0),setPoint(0,0,0));
  }
}



listObj createElt(object elt){
  listObj *list = (listObj*)malloc(sizeof(listObj));
  list->elt = elt;
  list->next = NULL;
  return list;
}

int addObjToList(listObj *head, object elt){
  if(head != NULL){
    listObj *currentElt = head;
    while(currentElt->next != NULL){
      currentElt = currentElt->next;
    }
    currentElt->next = createElt(elt);
    if(currentElt->next == NULL){
      return 0;
    }
    else{
      return 1;
    }
  }
  else{
    return 0;
  }
}

int deleteList(listObj *head){
  if(listObj != NULL){
    free(head);
  }
  else{
    return -1;
  }
}
