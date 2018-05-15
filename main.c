#include "bmp.h"
#include <stdio.h>
#include "geometric3DTools.h"
#include <stdlib.h>

int main(){
  image* I = newImage(200,200);
  point camera = setPoint(100,100,100);

  color blanc = setColor(255,255,255);
  color gris = setColor(144,144,144);
  color rougeClair = setColor(255,0,0);
  color rougeFonce = setColor(100,0,0);

  point tabPtsEcran[4];
  tabPtsEcran[0] = setPoint(0, 0, 200);
  tabPtsEcran[1] = setPoint(0, 0, 0);
  tabPtsEcran[2] = setPoint(200, 0, 0);
  tabPtsEcran[3] = setPoint(200, 0, 200);


  cartesianPlan sol;
  vector dir = setVector(tabPtsEcran[0], tabPtsEcran[1]);
  sol = setplanCartesian(dir, tabPtsEcran[0]);

  point* pointIntersect;
  point* pointIntersect2;
  point lamp = setPoint(100, -50, 400);
  ovoide S = setOvoide(100, -50, 100, 500, 2, 2, 2);
  int y = 0;

  for(int i = 0; i<200; i++){
    for(int j = 0; j<200; j++){
      point a = setPoint(i,y,j);
      halfLine hL = setHalfLine(camera, a);
      pointIntersect  = intersectSphereHalfLine(S, hL, camera);

      if(pointIntersect != NULL){
        printf("%d %d \n",i,j);
        halfLine hL2 = setHalfLine(lamp,*pointIntersect);
        pointIntersect2 = intersectSphereHalfLine(S, hL2, lamp);
        if(pointIntersect2 != NULL){
          if(comparePoints(*pointIntersect, *pointIntersect2)){
            setPixel(I,i,j,rougeClair);
          } else{
            setPixel(I,i,j,rougeFonce);
          }
        }
      }
      else if(intersectPlanHalfLine(sol, hL) != NULL){
        setPixel(I,i,j ,gris);
      }
      else{
        setPixel(I,i,j,blanc);
      }
    }

  }

  save(I, "img.bmp");
  delImage(I);
  return 0;
}
