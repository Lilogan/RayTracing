#include <stdio.h>
#include "geometric3DTools.h"
#include <stdlib.h>

int main(){
  image* I = newImage(1000,1000);
  point camera = setPoint(500,500,500);

  color blanc = setColor(255,255,255);
  color gris = setColor(144,144,144);
  color rougeClair = setColor(255,0,0);
  color rougeFonce = setColor(100,0,0);
  color noir = setColor(0,0,0);

  point tabPtsEcran[4];
  tabPtsEcran[0] = setPoint(0, 0, 1000);
  tabPtsEcran[1] = setPoint(0, 0, 0);
  tabPtsEcran[2] = setPoint(1000, 0, 0);
  tabPtsEcran[3] = setPoint(1000, 0, 1000);


  cartesianPlan sol;
  vector dir = setVector(tabPtsEcran[0], tabPtsEcran[1]);
  sol = setPlanCartesian(dir, tabPtsEcran[1]);

  point* pointIntersect = malloc(sizeof(point));
  point* pointIntersect2 = malloc(sizeof(point));
  point lamp = setPoint(700, -150, 1000);
  ovoide S = setOvoide(500, -250, 500, 5000, 2, 2, 2);
  int y = 0;

  for(int i = 0; i<1000; i++){
    for(int j = 0; j<1000; j++){
      point a = setPoint(i,y,j);
      halfLine hL = setHalfLine(camera, a);
      pointIntersect  = intersectSphereHalfLine(S, hL, camera);

      if(pointIntersect != NULL){
        halfLine hL2 = setHalfLine(lamp,*pointIntersect);
        pointIntersect2 = intersectSphereHalfLine(S, hL2, lamp);

        bool compar = comparePoints(*pointIntersect, *pointIntersect2);
        if(compar){
          setPixel(I,i,1000-j,rougeClair);
        }
        else{
          setPixel(I,i,1000-j,rougeFonce);
        }


      }
      else if(intersectPlanHalfLine(sol, hL) != NULL){
        point* pointIntersect3 = intersectPlanHalfLine(sol, hL);
        halfLine hL3;

        hL3 = setHalfLine(lamp, *pointIntersect3);
        if(intersectSphereHalfLine(S,hL3, lamp) != NULL){
          setPixel(I,i,1000-j ,noir);
        }
        else{
          setPixel(I,i,1000-j ,gris);
        }

      }
      else{
        setPixel(I,i,1000-j,blanc);
      }

    }

  }

  save(I, "img.bmp");
  delImage(I);
  return 0;
}
