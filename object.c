#include <stdlib.h>
#include "object.h"


material createMaterial(color oColor, float reflect, float transparency, float refraction){
  material mat;
  mat.oColor = oColor;
  mat.reflect = reflect;
  mat.transparency = transparency;
  mat.refraction = refraction;
  return mat;
}

object createObjectSpheroide(spheroide sp, material oMaterial){
  object obj;
  obj.type = "SP"; //spheroide = SP ; plan = PL ; solid = SO ; point : PT
  obj.parameter.sp = sp;
  obj.oMaterial = oMaterial;
  return obj;
}

object createObjectPlan(cartesianPlan pl, material oMaterial){
  object obj;
  obj.type = "PL";
  obj.parameter.pl = pl;
  obj.oMaterial = oMaterial;
  return obj;
}

object createObjectSolid(solid so, material oMaterial){
  object obj;
  obj.type = "SO";
  obj.parameter.so = so;
  obj.oMaterial = oMaterial;
  return obj;
}

object createObjectPoint(point pt, material oMaterial){
  object obj;
  obj.type = "PT";
  obj.parameter.pl = pt;
  obj.oMaterial = oMaterial;
  return obj;
}

point *intersectHalfLine(object obj, halfLine ray, point pointDistance){
  point *intersection;
  if(!strcmp(obj.type,"SP")){
     spheroide sp = obj.parameter.sp;
    intersection = intersectSpheroideHalfLine(sp,ray,pointDistance);
    return intersection;
  }
  if(!strcmp(obj.type,"PL")){
    parametricPlan pl = obj.parameter.pl;
    intersection = intersectPlanHalfLine(pl,ray);
    return intersection;
  }
  if(!strcmp(obj.type,"SO")){
    polygon so = obj.parameter.so;
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
     spheroide sp = obj.parameter.sp;
    normal = normalSpheroide(*sp,normalPoint);
    return normal;
  }
  if(!strcmp(obj.type,"PL")){
     parametricPlan pl = obj.parameter.pl;
    normal = normalPlan(pl,normalPoint);
    return normal;
  }
  if(!strcmp(obj.type,"SO")){
     solid *so = (solid)obj.parameter.so;
    normal = normalSolid(so,normalPoint);
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
