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

typedef struct headerImageBmp_{
  unsigned int sizeHeader;
  unsigned int width;
  unsigned int height;
  unsigned short planes;
  unsigned short bitCount;
  unsigned int compress;
  unsigned int sizeImg;
  unsigned int xPpm;
  unsigned int yPpm;
  unsigned int clrUsed;
  unsigned int clrImportant;
}headerImageBmp;

typedef struct headerBmp_{
  unsigned char type[2];
  unsigned int fileSize;
  unsigned int rsv;
  unsigned int offset;
}headerBmp;

image* newImage(int width,int height);
void setPixel(image*,int i,int j,pixel p);
pixel getPixel(image*,int i,int j);
int save(image*,const char* file);
void delImage(image*);
