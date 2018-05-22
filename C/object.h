#include "bmp.h"

typedef union surface_{
  spheroide sp;
  cartesianPlan pl;
  solid so;
  point pt;
}surface;

typedef struct material_{
  color oColor;
  float reflect;
  float transparency;
  float refraction;
}material;

typedef struct object_{
  char *type;   // spheroide = SP ; plan = PL ; solid = SO ; point : PT
  int id;
  surface parameter;
  material oMaterial;
}object;

typedef struct listObj_{
  object elt;
  struct listObj_ *next;
}listObj;


material createMaterial(color oColor, float reflect, float transparency, float refraction);
object createObjectSpheroide(spheroide sp, material oMaterial);
object createObjectPlan(cartesianPlan pl, material oMaterial);
object createObjectSolid(solid so, material oMaterial);
object createObjectPoint(point pt, material oMaterial);
point* intersectHalfLine(object obj, halfLine ray, point pointDistance);
vector normalObject(object obj, point normalPoint);

listObj *createElt(object elt);
int addObjToList(listObj *head, object elt);
int deleteList(listObj *head);
