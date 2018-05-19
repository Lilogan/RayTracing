#pragma pack(1)

typedef struct color_{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
}color;

typedef struct image_{
	int width;
	int height;
	color* data;
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

#pragma pack(8)

color setColor(unsigned char red, unsigned char green, unsigned char blue);
image* newImage(int width,int height);
void delImage(image*);
void setPixel(image*,int i,int j,color p);
color getColor(image*,int i,int j);
int save(image*,const char* fichier);

color addColor(color first, color second);
color substractColor(color first, color second);
color timesColor(color first, color second);
color timesColorNumber(color col, float nb);
