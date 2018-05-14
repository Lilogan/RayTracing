#include <stdlib.h>
#include "bmp.h"

int main() {
   image* I = newImage(256,256);
    for(int i=0;i<256;i++){
      for(int j=0;j<256;j++){
          pixel p;
          p.red = i;
          p.green = j;
          p.blue = 0;
          setPixel(I,i,j,p);
      }
    }
  save(I,"test.bmp");
  delImage(I);
  return 0;
  }
