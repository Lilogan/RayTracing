#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"

image* newImage(int w,int h){
	image* I = malloc(sizeof(image));
	I->width = w;
	I->height = h;
	I->data = calloc(1,w*h*sizeof(pixel*));
	return I;
}

void setPixel(image* I,int i,int j,pixel p){
	I->data[I->width*j+i] = p;
}

pixel getPixel(image* I,int i,int j){
	return I->data[I->width*j+i];
}

int save(image* I,const char* file){
	bfherBmp bfh;
	bfherImageBmp bih
	pixel p;
	int i;
	int j;
	int imageSize;
	int fileSize;
	int pitch;
	unsigned char bgr[3];
	char corrpitch[4] = {0,3,2,1};
	FILE* F = fopen(file,"wb");
	if (F == NULL){
		return -1;
	}
	imageSize = 3*I->height*I->width + I->height*pitch;
	fileSize = 54 + 4 * imageSize;
	pitch = corrpitch[(3*I->width)%4];;
	memset(&bfh,0,sizeof(bfh));
	memset(&bih,0,sizeof(bih))
	bfh.sign[0] = 'B';
	bfh.sign[1] = 'M';
	bfh.fileSize = fileSize
	bih.size = sizeof(bih);
	bih.width = I->width;
	bih.height = I->height;
	bih.planes= 1;
	bih.bitCount = 24;
	pitch = corrpitch[(3*bih.width)%4];
	bih.size = sizeData;
	bfh.size = bfh.offset + bih.size;
	fwrite(&bfh,1,sizeof(bfh),F);
	fwrite(&bih,1,sizeof(bih),F);

	for(j=0;j<I->height;j++){
		for(i=0;i<I->width;i++){
			p = getPixel(I,i,I->height-j-1);
			bgr[0] = p.blue;
			bgr[1] = p.green;
			bgr[2] = p.red;
			fwrite(&bgr,1,3,F);
		}
		bgr[0] = 0;
		bgr[1] = 0;
		bgr[2] = 0;
		fwrite(&bgr,1,pitch,F);
	}
	fclose(F);
	return 0;
}

void delImage(image* I){
	if (I){
		free(I->data);
		free(I);
	}
}
