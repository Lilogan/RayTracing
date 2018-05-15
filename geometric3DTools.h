#include <math.h>
#include <stdbool.h>

typedef struct point_ {
  //A = (x,y,z)
  float x;
  float y;
  float z;
} point;

typedef struct cartesianPlan_{
  //ax+by+cs+d=0
  float a;
  float b;
  float c;
  float d;
} cartesianPlan;

typedef struct vector_ {
  //A= (x,y,z)
  float x;
  float y;
  float z;
} vector;

typedef struct parametricPlan_{
  vector dir1;
  vector dir2;
  point point;
} parametricPlan;


typedef struct line_{
	vector dir;
  point point;
} line;

typedef struct halfLine_{
  // min = true => define a minimum
  // min = false => define a maximum
	vector dir;
  point point;
  bool min;
  float param;
} halfLine;

typedef struct polygon_{
  int pointNbre;
  point* vertex;
} polygon;

typedef struct surface_{
  // ax + by + cz + d = 0 avec degrés 
  float a;
  float b;
  float c;
  float d;
  int degX
  int degY
  int degZ
} surface;

vector qTimeVector(int k, vector u);//done

vector addVectors(vector u, vector v);//done

vector substractVectors(vector u, vector v);//done

float scalarVectors(vector u, vector v);//done

float normVector(vector u);//done

vector productVector(vector u, vector v);//done

point intersect(cartesianPlan p, halfLine d); // done

vector reflect(halfLine i, cartesianPlan p); //done

vector refracte(halfLine i, cartesianPlan p);

cartesianPlan firstPlanIntersect(line line);

vector normal(cartesianPlan p);//done
