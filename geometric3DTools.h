#include <math.h>

typedef struct point_ {
  //A = (x,y,z)
  float x;
  float y;
  float z;
} point;

typedef struct cartesianPlane_{
  //ax+by+cs+d=0
  float a;
  float b;
  float c;
  float d;
}cartesianPlane;

typedef struct parametricPlane_{
  vecteur dir1;
  vecteur dir2;
  point point;
} parametricPlane;

typedef struct vector_ {
  //A= (x,y,z)
  float x;
  float y;
  float z;
}vector;

typedef struct line_{
	vecteur dir;
  point point;
}line;

typedef struct halfLine_{
	vecteur dir;
  point point;
  float paramMin;
}halfLine;

typedef struct polygon_{
  int pointNbre;
  point* vertex;
}polygon;

vector qTimeVector(int k, vector u);

vector addVectors(vector u, vector v);

vector substractVectors(vector u, vector v);

vector scalarVectors(vector u, vector v);

float normVector(vector u);

vector productVector(vector u, vector v);

point intersect(cartesianPlane p, line d);

vector reflect(vector i, cartesianPlane p);

vector refracte(vector i, cartesianPlane p);

cartesianPlane firstPlaneIntersect(line line);

vector normal(cartesianPlane p);
