#include "geometric3DTools.h"
#include "bmp.h"
#include <string.h>

typedef union surface_{
  spheroide sp;
  plan pl;
  solid so;
  point pt;
}surface;

typedef struct material_{
  color oColor;
  float reflect;
  float transparency;
  float refaction;
}material;

typedef struct object_{
  char *type;   // spheroide = SP ; plan = PL ; solid = SO ; point : PT
  surface parameter;
  material oMaterial;
}object;

typedef struct listObj_{
  object elt;
  struct listObj_ *next;
}listObj;


material createMaterial(color oColor, float reflect, float transparency, float refraction);
object createObject(char *type , void *parameter, material oMaterial);
point* intersectHalfLine(object obj, halfLine ray, point pointDistance);
vector normalObject(object obj, point normalPoint);

listObj createElt(object elt);
int addObjToList(listObj *head, object elt);
int deleteList(listObj *head);
