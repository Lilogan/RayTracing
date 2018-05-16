#include "object.h"

object createObject(char *type , void *parameter, color oColor){
  object obj;
  obj.type = type;
  obj.parameter = parameter;
  obj.oColor = oColor;
  return obj;
}

point *intersectHalfLine(object obj, halfLine ray, point pointDistance){
  point *intersection;
  if(!strcmp(obj.type,"SP")){
     spheroid *sp = (spheroid)obj.parameter;
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
};
