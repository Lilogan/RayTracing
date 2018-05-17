#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct point_ {
  //A = (x,y,z)
  float x;
  float y;
  float z;
} point;

typedef struct cartesianPlan_{
  //ax+by+cz+d=0
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
  point randPoint;
  bool min;
  float param;
} halfLine;

typedef struct polygon_{
  int pointNbr;
  point* vertex;
} polygon;

typedef struct solid_{
  int nbPolygon;
  polygon* tabPolygon;
} solid;

typedef struct spheroide_{
  // ax² + by² + cz² + dyz + exz + fxy + gx + hy + iz + j = 0 avec degrés
  float a;
  float b;
  float c;
  float d;
  float e;
  float f;
  float g;
  float h;
  float i;
  float j;
  float k; // <- x0
  float l; // <- y0
  float m; // <- z0
} spheroide;

point setPoint(int x, int y, int z); //done

vector setVector(point a, point b); //done

polygon setPolygon(int pointNbr, point* vertex); //done

spheroide setSpheroide(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j , float k, float l , float m);//done

cartesianPlan setPlanCartesian(vector normal, point randPoint); //done

halfLine setHalfLine(point origin, point randPoint); //done

vector qTimeVector(int k, vector u);//done

vector addVectors(vector u, vector v);//done

vector substractVectors(vector u, vector v);//done

float normVector(vector u);//done

float scalarVectors(vector u, vector v);//done

vector productVector(vector u, vector v);//done

float calculParam(cartesianPlan p, halfLine d); //done

point* intersectPlanHalfLine(cartesianPlan p, halfLine d); // done

vector normal(cartesianPlan p);//done

// vector refracte(halfLine i, cartesianPlan p);

// cartesianPlan firstPlanIntersect(line line);

vector reflect(halfLine i, cartesianPlan p); //done

cartesianPlan definePlan(vector dir1, vector dir2, point insidePoint); //done

cartesianPlan polygonPlan(polygon inputPolygon); //done

bool isRayInpolygon(polygon inputPolygon, halfLine ray);//done

float distancePoints(point a, point b); //done

point* intersectSpheroideHalfLine(spheroide spheroide, halfLine ray, point pointDistance); //done

bool comparePoints(point a, point b);

vector normalSpheroide(spheroide inputSpheroide, point normalPoint);

vector normalizeVector(vector inputVector);

double cosVector(vertor first, vector second);
