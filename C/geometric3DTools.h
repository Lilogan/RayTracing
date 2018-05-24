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

solid setSolid(int nbPolygon, polygon* tabPolygon);

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

vector normalPlan(cartesianPlan p, vector incident);//done

// vector refracte(halfLine i, cartesianPlan p);printf("interse plan\n")printf("interse plan\n");;

// cartesianPlan firstPlanIntersect(line line);

vector reflectPlan(halfLine i, cartesianPlan p); //done

cartesianPlan definePlan(vector dir1, vector dir2, point insidePoint); //done

cartesianPlan polygonPlan(polygon inputPolygon); //done

float distancePoints(point a, point b);

point* intersectPolygon(polygon inputPolygon, halfLine ray);//done

point* intersectSpheroideHalfLine(spheroide spheroide, halfLine ray, point pointDistance); //done

point* intersectSolidHalfLine(solid so, halfLine ray, point distancePoint);

polygon closestPolygon(solid sol, halfLine ray);

bool comparePoints(point a, point b);

vector normalSpheroide(spheroide inputSpheroide, point normalPoint);

vector normalizeVector(vector inputVector);

double cosVector(vector first, vector second);

point translate(point pt, vector vec);

vector normalSolid(solid inputSolid, halfLine incident);
