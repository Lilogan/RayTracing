#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"

color setColor(unsigned char red, unsigned char green, unsigned char blue){
	color col;
	col.red = red;
	col.green = green;
	col.blue = blue;
	return col;
}

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

color addColor(color first, color second){
	int red = first.red + second.red;
	if(red > 255){
		red = 255;
	}
	int green = first.green + second.green;
	if(green > 255){
		green = 255;
	}
	int blue = first.blue + second.blue;
	if(blue > 255){
		blue = 255;
	}
	color result = setColor((char)red,(char)green,(char)blue);
	return result;
}

color substractColor(color first, color second){
	int red = first.red - second.red;
	if(red < 0){
		red = 0;
	}
	int green = first.green - second.green;
	if(green < 0){
		green = 0;
	}
	int blue = first.blue - second.blue;
	if(blue < 0){
		blue = 0;
	}
	color result = setColor((char)red,(char)green,(char)blue);
	return result;
}

color timesColor(color first, color second){
	double red = (first.red/255 * second.red/255)*255;
	double green = (first.green/255 * second.green/255)*255;
	double blue = (first.blue/255 * second.blue/255)*255;
	color result = setColor((char)red,(char)green,(char)blue);
	return result;
};
color timesColorNumber(color col, float nb){
	if (nb < 0){
		nb = -nb;
	}
	double red = col.red + nb;
	if(red > 255){
		red = 255;
	}
	double green = col.green + nb;
	if(green > 255){
		green = 255;
	}
	double blue = col.blue + nb;
	if(blue > 255){
		blue = 255;
	}
	color result = setColor((char)red,(char)green,(char)blue);
	return result;
};
