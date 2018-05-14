#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"

Image* NouvelleImage(int w,int h){
	Image* I = malloc(sizeof(Image));
	I->w = w;
	I->h = h;
	I->dat = calloc(1,w*h*sizeof(Pixel*));
	return I;
}

void SetPixel(Image* I,int i,int j,Pixel p){
	I->dat[I->w*j+i] = p;
}

Pixel GetPixel(Image* I,int i,int j){
	return I->dat[I->w*j+i];
}

int Sauver(Image* I,const char* fichier){
	Pixel p;
	int i;
	int j
	int tailledata;
	int pitch;
	unsigned char brg[3];
	char corrpitch[4] = {0,3,2,1};
	FILE* F = fopen(fichier,"w+");
	if (F == NULL){
		return -1;
	}

	// fwrite();  Header


	for(j=0;j<I->h;j++)
	{
		for(i=0;i<I->w;i++)
		{
			p = GetPixel(I,i,I->h-j-1);
			bgr[0] = p.b;
			bgr[1] = p.g;
			bgr[2] = p.r;
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
