#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "geometric3DTools.h"
#include "object.h"
#include <time.h>

int id = 0;

int addId(){
  int send = id;
  id++;
  printf("id : %d\n",send);
  return send;
}

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
  obj.id = addId();
  obj.parameter.sp = sp;
  obj.oMaterial = oMaterial;
  return obj;
}

object createObjectPlan(cartesianPlan pl, material oMaterial){
  object obj;
  obj.type = "PL";
  obj.id = addId();
  obj.parameter.pl = pl;
  obj.oMaterial = oMaterial;
  return obj;
}

object createObjectSolid(solid so, material oMaterial){
  object obj;
  obj.type = "SO";
  obj.id = addId();
  obj.parameter.so = so;
  obj.oMaterial = oMaterial;
  return obj;
}

object createObjectPoint(point pt, material oMaterial){
  object obj;
  obj.type = "PT";
  obj.id = addId();
  obj.parameter.pt = pt;
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
    cartesianPlan pl = obj.parameter.pl;
    intersection = intersectPlanHalfLine(pl,ray);
    return intersection;
  }
  /*if(!strcmp(obj.type,"SO")){
    polygon so = obj.parameter.so;
    intersection = intersectSolidHalfLine(*po,ray);
    return intersection;
  }
  if(!strcmp(obj.type,"PT")){
    return NULL;
  }*/
  return NULL;
}

vector normalObject(object obj, point normalPoint){
  vector normal;
  if(!strcmp(obj.type,"SP")){
     spheroide sp = obj.parameter.sp;
    normal = normalSpheroide(sp,normalPoint);
    return normal;
  }
  if(!strcmp(obj.type,"PL")){
     cartesianPlan pl = obj.parameter.pl;
    normal = normalPlan(pl);
    return normal;
  }
  /*if(!strcmp(obj.type,"SO")){
     solid *so = (solid)obj.parameter.so;
    normal = normalSolid(so,normalPoint);
    return normal;
  }
  if(!strcmp(obj.type,"PT")){
    return setVector(setPoint(0,0,0),setPoint(0,0,0));
  }*/
  return setVector(setPoint(0,0,0),setPoint(0,0,0));
}



listObj *createElt(object elt){
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
  if(head != NULL){
    free(head);
    return 0;
  }
  else{
    return -1;
  }
}
