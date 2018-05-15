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

typedef struct color_{
  int r;
  int g;
  int b;
} color;

typedef struct polygon_{
  int pointNbr;
  point* vertex;
  color color;
} polygon;

typedef struct ovoide_{
  // ax + by + cz + d = 0 avec degrés
  float a;
  float b;
  float c;
  float d;
  int degX
  int degY
  int degZ
} ovoide;

point setPoint(int x, int y, int z); //done

vector setVector(point a, point b); //done

polygon setPolygon(int pointNbr, point* vertex); //done

halfLine setHalfLine(point origin, point randPoint);

ovoide setOvoide();

vector qTimeVector(int k, vector u);//done

vector addVectors(vector u, vector v);//done

vector substractVectors(vector u, vector v);//done

float normVector(vector u);//done

float scalarVectors(vector u, vector v);//done

vector productVector(vector u, vector v);//done

float calculParam(cartesianPlan p, halfLine d); //done

point intersectPlanHalfLine(cartesianPlan p, halfLine d); // done

vector normal(cartesianPlan p);//done

// vector refracte(halfLine i, cartesianPlan p);

// cartesianPlan firstPlanIntersect(line line);

vector reflect(halfLine i, cartesianPlan p); //done

cartesianPlan definePlan(vector dir1, vector dir2, point insidePoint); //done

cartesianPlan planOfPolygon(polygon inputPolygon); //done

bool isRayInpolygon(polygon inputPolygon, halfLine ray);//done
