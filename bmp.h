typedef struct Pixel_{
	unsigned char red;
  unsigned char green;
  unsigned char blue;
}Pixel;

typedef struct Image_{
	int width;
  int height;
	Pixel* dat;
}Image;

typedef struct ImgHeadBmp_{
  int sizeImgHead;
  int width;
  int height;
  short nbPlan;
  short bpp;
  int compression;
  int sizeImg;
  int hRes;
  int vRes;
  int colPalette;
  int imColPalette;
}ImgHeadBmp;

typedef struct HeadBmp_{
  short sign;
  int taille;
  int rsv;
  int offset;
  ImgHeadBmp imgHead;
}HeadBmp;

Image* NouvelleImage(int w,int h);
void SetPixel(Image*,int i,int j,Pixel p);
Pixel GetPixel(Image*,int i,int j);
int Sauver(Image*,const char* fichier);
