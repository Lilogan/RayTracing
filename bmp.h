#pragma pack(1) 

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

struct bmpImageHead{
	int sizeHeader;
	int width;
	int height;
	short planes;
	short bitCount;
	int compress;
	int sizeImage;
	int xPpm;
	int yPpm;
	int clrUsed;
	int clrImportant;
};

struct bmpFileHead{
	char type[2];
	int sizeFile;
	int reserved;
	int offset;
	struct bmpImageHead bih;
};

int save(image*,const char* fichier);
image* newImage(int width,int height);
void setPixel(image*,int i,int j,pixel p);
pixel getPixel(image*,int i,int j);
void delImage(image*);
