#include "bmp.h"
#include "geometric3DTools.h"
#include <stdlib.h>

int main(){
  image* I = newImage(200,200);
  point camera = setPoint(0,-100,0);

  color blanc = setColor(255,255,255);
  color noir = setColor(0,0,0);
  color rougeClair = setColor(255,0,0);
  color rougeFonce = setColor(100,0,0);

  point tabPtsEcran[4];
  tabPtsEcran[0] = setPoint(-100, 0, -50);
  tabPtsEcran[1] = setPoint(100, 0, -50);
  tabPtsEcran[2] = setPoint(100, 0, 50);
  tabPtsEcran[3] = setPoint(-100, 0, 50);


  cartesianPlan sol;
  vector dir = setVector(tabPtsEcran[0], tabPtsEcran[11]);
  sol = setplanCartesian(dir, tabPtsEcran[0]);

  point* pointIntersect;
  point* pointIntersect2;
  point lamp = setPoint(-75, 50, 35);
  ovoide S = setOvoide(12.74, 75, 0, 93, 2, 2, 2);
  int y = 0;
  for(int i = -100; i<100; i++){
    for(int j = -100; j<100; j++){
      point a = setPoint(i,y,j);
      halfLine hL = setHalfLine(camera, a);
      pointIntersect  = intersectSphereHalfLine(S, hL, camera);

      if(pointIntersect != NULL){
        halfLine hL2 = setHalfLine(lamp, *pointIntersect);
        pointIntersect2 = intersectSphereHalfLine(S, hL2, lamp);

        if(comparePoints(*pointIntersect, *pointIntersect2)){
          setPixel(I,i + 100,j + 100,rougeClair);
        } else{
          setPixel(I,i + 100,j + 100,rougeFonce);
        }

      } else if(intersectPlanHalfLine(sol, hL) != NULL){
        setPixel(I,i + 100,j + 100,noir);
      } else{
        setPixel(I,i + 100,j + 100,blanc);
      }
    }

  }

  save(I, "img.bmp");
  delImage(I);
  return 0;
}
