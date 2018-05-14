#include <math.h>
#include <stdbool.h>

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
  // min = true => define a minimum
  // min = false => define a maximum
	vecteur dir;
  point point;
  bool min;
  float param;
}halfLine;

typedef struct polygon_{
  int pointNbre;
  point* vertex;
}polygon;

vector qTimeVector(int k, vector u);//done

vector addVectors(vector u, vector v);//done

vector substractVectors(vector u, vector v);//done

vector scalarVectors(vector u, vector v);//done

float normVector(vector u);//done

vector productVector(vector u, vector v);//done

point intersect(cartesianPlane p, halfLine d);

vector reflect(line i, cartesianPlane p);

vector refracte(vector i, cartesianPlane p);

cartesianPlane firstPlaneIntersect(line line);

vector normal(cartesianPlane p);
