#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"

image* newImage(int width,int height){
	image* I = malloc(sizeof(image));
	I->width = width;
	I->height = height;
	I->data = calloc(1,width*height*sizeof(color*));
	return I;
}

void delImage(image* I){
	if (I != NULL){
		free(I->data);
		free(I);
	}
}

void setPixel(image* I,int i,int j,color p){
	if(I && i>=0 && i<I->width && j>=0 && j<I->height){
		I->data[I->width*j+i] = p;
	}
}

color getColor(image* I,int i,int j){
	if(I && i>=0 && i<I->width && j>=0 && j<I->height){
		return I->data[I->width*j+i];
	}
}

int save(image* I,const char* fichier)
{
	struct bmpFileHead bfh;
	color p;
	int width = I->width;
	int height = I->height;
	int offset = sizeof(struct bmpFileHead);
	int sizeHeader = sizeof(struct bmpImageHead);
	char corrpitch[4] = {0,3,2,1};
	int pitch = corrpitch[(3*width)%4];
	int sizeImage = 3*height*width + height*pitch;
	unsigned char bgr[3];

	FILE* F = fopen(fichier,"wb");
	if (!F){
		return -1;
	}

	memset(&bfh,0,sizeof(struct bmpFileHead));
	bfh.type[0] = 'B';
	bfh.type[1] = 'M';
	bfh.sizeFile = offset + sizeImage;
	bfh.offset = offset;
	bfh.bih.sizeHeader = sizeHeader;
	bfh.bih.width = width;
	bfh.bih.height = height;
	bfh.bih.sizeImage = sizeImage;
	bfh.bih.planes = 1;
	bfh.bih.bitCount = 24;
	fwrite(&bfh,sizeof(struct bmpFileHead),1,F);

	for(int j=0;j<height;j++){
		for(int i=0;i<width;i++){
			p = getColor(I,i,height-j-1);
			bgr[0] = p.blue;
			bgr[1] = p.green;
			bgr[2] = p.red;
			fwrite(&bgr,1,3,F);
		}
		bgr[0] = bgr[1] = bgr[2] = 0;
		fwrite(&bgr,1,pitch,F);
	}
	fclose(F);
	return 0;
}
