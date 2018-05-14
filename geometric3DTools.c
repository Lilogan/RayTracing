#include <math.h>

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

vector scalarVectors(vector u, vector v){
  return 1 / 2 * (normevector(u) + normevector(v) - normevector(soustractionvector(v, u)));
}

vector productVector(vector u, vector v){
  vector w;
  w.x = u.y * v.z - u.z * v.y;
  w.y = u.z * v.x - u.x * v.z;
  w.z = u.x * v.y - u.y * v.x;
  return w;
}

point intersect(cartesianplan p, halfLine d){
  float calculatedParam;
  point returnedPoint = NULL;
  calculatedParam = -(p.a*d.point.x + p.b*d.point.y + p.c*d.point.x +p.d)
  calculatedParam = calculatedParam/(p.a*d.dir.x + p.b*d.dir.y + p.c*d.dir.z)

  if(halfLine.min == true && halfLine.param <= calculatedParam){
    returnedPoint.x = d.point.x + d.dir.x*calculatedParam;
    returnedPoint.y = d.point.y + d.dir.y*calculatedParam;
    returnedPoint.z = d.point.z + d.dir.z*calculatedParam;
  }
  else if(halfLine.min == false && halfLine.param >= calculatedParam){
    returnedPoint.x = d.point.x + d.dir.x*calculatedParam;
    returnedPoint.y = d.point.y + d.dir.y*calculatedParam;
    returnedPoint.z = d.point.z + d.dir.z*calculatedParam;
  }

  return returnedPoint;

}
