#include "bmp.h"
#include <stdio.h>
#include "geometric3DTools.h"
#include <stdlib.h>

int main(){
  image* I = newImage(200*5  ,200*5);
  point camera = setPoint(100*5,100*5,100*5);

  color blanc = setColor(255,255,255);
  color gris = setColor(144,144,144);
  color rougeClair = setColor(255,0,0);
  color rougeFonce = setColor(100,0,0);
  color noir = setColor(0,0,0);


  point tabPtsEcran[4];
  tabPtsEcran[0] = setPoint(0, 0, 200*5);
  tabPtsEcran[1] = setPoint(0, 0, 0);
  tabPtsEcran[2] = setPoint(200*5, 0, 0);
  tabPtsEcran[3] = setPoint(200*5, 0, 200*5);


  cartesianPlan sol;
  vector dir = setVector(tabPtsEcran[0], tabPtsEcran[1]);
  sol = setPlanCartesian(dir, tabPtsEcran[1]);

  point* pointIntersect = malloc(sizeof(point));
  point* pointIntersect2 = malloc(sizeof(point));
  point lamp = setPoint(200*5, 0, 200*5);
  spheroide S = setSpheroide(pow(100,-2),pow(100,-2),pow(200,-2),0,0,0,0,0,0, 1,100*5, -200, 100*5);
  int y = 0;

  for(int i = 0; i<200*5; i++){
    for(int j = 0; j<200*5; j++){
      point a = setPoint(i,y,j);
      halfLine hL = setHalfLine(camera, a);
      pointIntersect  = intersectSpheroideHalfLine(S, hL, camera);

      if(pointIntersect != NULL){
        halfLine hL2 = setHalfLine(lamp,*pointIntersect);
        pointIntersect2 = intersectSpheroideHalfLine(S, hL2, lamp);

        if(pointIntersect2!=NULL){
          bool compar = comparePoints(*pointIntersect, *pointIntersect2);
          if(compar){
            setPixel(I,i,200*5-j,rougeClair);
          }
          else{
            setPixel(I,i,200*5-j,rougeFonce);
          }
        }
        else{
          setPixel(I,i,200*5-j,rougeClair);
        }


      }
      else if(intersectPlanHalfLine(sol, hL) != NULL){
        point* pointIntersect3 = intersectPlanHalfLine(sol, hL);
        halfLine hL3;

        hL3 = setHalfLine(lamp, *pointIntersect3);
        if(intersectSpheroideHalfLine(S,hL3, lamp) != NULL){
          setPixel(I,i,200*5-j ,noir);
        }
        else{
          setPixel(I,i,200*5-j ,gris);
        }

      }
      else{
        setPixel(I,i,200*5-j,blanc);
      }

    }

  }

  save(I, "img.bmp");
  delImage(I);
  return 0;
}
