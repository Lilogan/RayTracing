typedef struct pixel_{
	unsigned char red;
  unsigned char green;
  unsigned char blue;
}pixel;

typedef struct image_{
	int width;
  int height;
	pixel* data;
}image;

typedef struct imgHeadBmp_{
  int size;
  int width;
  int height;
  short nbPlan;
  short bpp;
  int compress;
  int sizeImg;
  int hRes;
  int vRes;
  int colPalette;
  int imColPalette;
}imgHeadBmp;

typedef struct headBmp_{
  char sign[2];
  int size;
  int rsv;
  int offset;
  imgHeadBmp imgHead;
}headBmp;

image* newImage(int width,int height);
void setPixel(image*,int i,int j,pixel p);
pixel getPixel(image*,int i,int j);
int save(image*,const char* file);
void delImage(image*);
