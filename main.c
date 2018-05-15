#include "geometric3DTools.h"

int main(){
  point camera = setPoint(0,-50,0);

  point tabPts[4];
  tabPts[0] = setPoint(-100, 0, -50);
  tabPts[1] = setPoint(100, 0, -50);
  tabPts[2] = setPoint(100, 0, 50);
  tabPts[3] = setPoint(-100, 0, 50);

  polygon ecran = setPolygon(4, tabPts);

  return 0;
}
