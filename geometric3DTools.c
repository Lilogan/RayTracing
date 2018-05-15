#include <math.h>
#include "geometric3DTools.h"

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
}

vector productVector(vector u, vector v){
  vector w;
  w.x = u.y * v.z - u.z * v.y;
  w.y = u.z * v.x - u.x * v.z;
  w.z = u.x * v.y - u.y * v.x;
  return w;
}

point intersect(cartesianPlan p, halfLine d){
  float calculatedParam;
  point returnedPoint;
  calculatedParam = -(p.a*d.point.x + p.b*d.point.y + p.c*d.point.z +p.d);
  calculatedParam = calculatedParam/(p.a*d.dir.x + p.b*d.dir.y + p.c*d.dir.z);

  if(d.min == true && d.param <= calculatedParam){
    returnedPoint.x = d.point.x + d.dir.x*calculatedParam;
    returnedPoint.y = d.point.y + d.dir.y*calculatedParam;
    returnedPoint.z = d.point.z + d.dir.z*calculatedParam;
  else if(d.min == false && d.param >= calculatedParam){
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
  vector normal;
  float incidentNorm;
  float normalNorm;
  incident = i.dir;
  incidentNorm = pow(normVector(incident),-1);
  normal = normal(p);
  normalNorm = pow(normVector(normal),-1);

  float cosinus = scalarVectors(qTimeVector(normalNorm,normal), qTimeVector(-1*incidentNorm,incident));

  if(cosinus >= -1 && cosinus <= 1){
    reflected = qTimeVector(incidentNorm, incident) + 2*cosinus*qTimeVector(normalNorm, normal);
  }
  else{
    reflected.x = 0;
    reflected.y = 0;
    reflected.z = 0;
  }

  return reflected;
}
