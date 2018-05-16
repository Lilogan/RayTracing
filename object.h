#include "geometric3DTools.h"
#include "bmp.h"
#include <string.h>

typedef struct object_{
  char *type;   // spheroid = SP ; plan = PL ; solid = SO ; point : PT
  void *parameter;
  color oColor;
  // material oMaterial;
}object;

typedef struct listObj_{
  object elt;
  struct listObj_ *next;
}listObj;


object createObject(char *type , void *parameter, color oColor);
point* intersectHalfLine(object obj, halfLine ray, point pointDistance);
listObj createElt(object elt);
int addObjToList(listObj *head, object elt);
int deleteList(listObj *head);
