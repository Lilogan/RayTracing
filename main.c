#include "bmp.h"
#include <stdio.h>
#include "geometric3DTools.h"
#include <stdlib.h>

int main(){
  int width = 1000;
  int height = 1000;
  int distanceCameraEcran = 500;
  int distanceSpheroideEcran = -750;
  int rayonSpheroide = 200;

  image* I = newImage(width, height);
  point camera = setPoint(width/2, distanceCameraEcran, height/2);
  point lamp = setPoint(width, 0, height);
  spheroide S = setSpheroide(width/2, distanceSpheroideEcran, 200, pow(rayonSpheroide, 2), 2, 2, 2);

  color blanc = setColor(255,255,255);
  color gris = setColor(144,144,144);
  color rougeClair = setColor(255,0,0);
  color rougeFonce = setColor(100,0,0);
  color noir = setColor(0,0,0);


  point tabPtsEcran[2];
  tabPtsEcran[0] = setPoint(0, 0, height);
  tabPtsEcran[1] = setPoint(0, 0, 0);

  cartesianPlan sol;
  vector dir = setVector(tabPtsEcran[0], tabPtsEcran[1]);
  sol = setPlanCartesian(dir, tabPtsEcran[1]);

  point* pointIntersect = malloc(sizeof(point));
  point* pointIntersect2 = malloc(sizeof(point));

  for(int i = 0; i<width; i++){
    for(int j = 0; j<height; j++){
      point a = setPoint(i,0,j);
      halfLine hL = setHalfLine(camera, a);
      pointIntersect  = intersectSpheroideHalfLine(S, hL, camera);

      if(pointIntersect != NULL){
        halfLine hL2 = setHalfLine(lamp, *pointIntersect);
        pointIntersect2 = intersectSpheroideHalfLine(S, hL2, lamp);

        if(pointIntersect2!=NULL){
          bool compar = comparePoints(*pointIntersect, *pointIntersect2);
          if(compar){
            setPixel(I, i, height-j, rougeClair);
          }
          else{
            setPixel(I, i, height-j, rougeFonce);
          }
        }
        else{
          setPixel(I, i, height-j, rougeClair);
        }
      } else if(intersectPlanHalfLine(sol, hL) != NULL){
        point* pointIntersect3 = intersectPlanHalfLine(sol, hL);
        halfLine hL3 = setHalfLine(lamp, *pointIntersect3);

        if(intersectSpheroideHalfLine(S, hL3, lamp) != NULL){
          setPixel(I, i, height-j, noir);
        } else{
          setPixel(I, i, height-j, gris);
        }

      } else{
        setPixel(I, i, height-j, blanc);
      }
    }
  }

  save(I, "img.bmp");
  delImage(I);
  return 0;
}
