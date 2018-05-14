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
	headBmp head;
	pixel p;
	int i;
	int j;
	int sizedata;
	int pitch;
	unsigned char bgr[3];
	char corrpitch[4] = {0,3,2,1};
	FILE* F = fopen(file,"w+");
	if (F == NULL){
		return -1;
	}
	memset(&head,0,sizeof(headBmp));
	head.sign[0] = 'B';
	head.sign[1] = 'M';
	head.offset = sizeof(headBmp);
	head.imgHead.size = sizeof(imgHeadBmp);
	head.imgHead.width = I->width;
	head.imgHead.height = I->height;
	head.imgHead.nbPlan = 1;
	head.imgHead.bpp = 24;
	pitch = corrpitch[(3*head.imgHead.width)%4];
	sizedata = 3*head.imgHead.height*head.imgHead.width + head.imgHead.height*pitch;
	head.imgHead.size = sizedata;
	head.size = head.offset + head.imgHead.size;
	fwrite(&head,sizeof(headBmp),1,F);

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
