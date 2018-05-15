#include <math.h>
#include "geometric3DTools.h"

point setCamera(int x, int y, int z){
  point camera;
  point.x = x;
  point.y = y;
  point.z = z;
  
  return point;
}

vector setVector(point a, point b){
  vector u;
  u.x = b.x - a.x;
  u.y = b.y - a.y;
  u.z = b.z - a.z;
  return u;
}

vector qTimeVector(int k, vector u){
  u.x = k * u.x;
  u.y = k * u.y;
  u.z = k * u.z;
  return u;
}

vector addVectors(vector u, vector v){
  vector w;
  w.x = u.x + v.x;
  w.y = u.y + v.y;
  w.z = u.z + v.z;
  return w;
}

vector substractVectors(vector u, vector v){
  vector w;
  w.x = u.x - v.x;
  w.y = u.y - v.y;
  w.z = u.z - v.z;
  return w;
}

float normVector(vector u){
  return sqrt(pow(u.x, 2) + pow(u.y, 2) + pow(u.z, 2));
}

float scalarVectors(vector u, vector v){
  return 1 / 2 * (normVector(u) + normVector(v) - normVector(substractVectors(v, u)));
}

vector productVector(vector u, vector v){
  vector w;
  w.x = u.y * v.z - u.z * v.y;
  w.y = u.z * v.x - u.x * v.z;
  w.z = u.x * v.y - u.y * v.x;
  return w;
}

float calculParam(cartesianPlan p, halfLine d){
  float calculatedParam;
  calculatedParam = (-1 * (p.a * d.point.x + p.b * d.point.y + p.c * d.point.x + p.d)) / (p.a * d.dir.x + p.b * d.dir.y + p.c * d.dir.z);

  return calculatedParam;
}

point intersect(cartesianPlan p, halfLine d){
  float calculatedParam = calculParam(p, d);
  point returnedPoint;

  if(d.min == true && d.param <= calculatedParam){
    returnedPoint.x = d.point.x + d.dir.x*calculatedParam;
    returnedPoint.y = d.point.y + d.dir.y*calculatedParam;
    returnedPoint.z = d.point.z + d.dir.z*calculatedParam;
  } else if(d.min == false && d.param >= calculatedParam){
    returnedPoint.x = d.point.x + d.dir.x*calculatedParam;
    returnedPoint.y = d.point.y + d.dir.y*calculatedParam;
    returnedPoint.z = d.point.z + d.dir.z*calculatedParam;
  }

  return returnedPoint;

}

vector normal(cartesianPlan p){
  vector normal;
  normal.x = p.a;
  normal.y = p.b;
  normal.z = p.c;
  return normal;
}

vector reflect(halfLine i, cartesianPlan p){
  vector incident;
  vector reflected;
  vector normalVec;
  float incidentNorm;
  float normalNorm;
  incident = i.dir;
  incidentNorm = pow(normVector(incident),-1);
  normalVec = normal(p);
  normalNorm = pow(normVector(normalVec),-1);

  float cosinus = scalarVectors(qTimeVector(normalNorm,normalVec), qTimeVector(-1*incidentNorm,incident));

  if(cosinus >= -1 && cosinus <= 1){
    reflected = addVectors(qTimeVector(incidentNorm, incident), qTimeVector(2*cosinus,qTimeVector(normalNorm, normalVec)));
  }
  else{
    reflected.x = 0;
    reflected.y = 0;
    reflected.z = 0;
  }

  return reflected;
}

bool inRayInpolygon(polygon inputPolygon, halfLine ray){
  int nbreVertex;
  vector vectorDir1;
  vector vectorDir2;

  nbreVertex = inputPolygon.pointNbre;

  if(nbreVertex > 2){
    vectorDir1 = setVector(*inputPolygon.vertex, *(inputPolygon.vertex+1));
    vectorDir1 = setVector(*inputPolygon.vertex, *(inputPolygon.vertex+2));
  }
}
