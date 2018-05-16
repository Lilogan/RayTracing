#include "geometric3DTools.h"
#include "bmp.h"
#include <string.h>

typedef struct object_{
  char *type;   // spheroid = SP ; plan = PL ; solid = SO
  void *parameter;
  color oColor;
  // material oMaterial;
}object;

object createObject(char *type , void *parameter, color oColor);
point* intersectHalfLine(object obj, halfLine ray, point pointDistance);
