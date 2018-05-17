#include "geometric3DTools.h"
#include <stdlib.h>

point setPoint(int x, int y, int z){
  point a;
  a.x = x;
  a.y = y;
  a.z = z;
  return a;
}

vector setVector(point a, point b){
  vector u;
  u.x = b.x - a.x;
  u.y = b.y - a.y;
  u.z = b.z - a.z;
  return u;
}

polygon setPolygon(int pointNbr, point* vertex){
  polygon poly;
  poly.pointNbr = pointNbr;
  poly.vertex = vertex;
  return poly;
}

spheroide setSpheroide(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j , float k, float l , float m){
  spheroide s;
  s.a = a;
  s.b = b;
  s.c = c;
  s.d = d;
  s.e = e;
  s.f = f;
  s.g = g;
  s.h = h;
  s.i = i;
  s.j = j;
  s.k = k;
  s.l = l;
  s.m= m;

  return s;
}

cartesianPlan setPlanCartesian(vector normal, point randPoint){
  cartesianPlan returned;
  returned.a = normal.x;
  returned.b = normal.y;
  returned.c = normal.z;
  returned.d = -(normal.x * randPoint.x + normal.y * randPoint.y + normal.z * randPoint.z);
  return returned;
}

halfLine setHalfLine(point origin, point randPoint){
  vector dir;
  halfLine returned;
  dir = setVector(origin, randPoint);
  returned.dir = dir;
  returned.randPoint = origin;
  returned.min = true;
  returned.param = 0;
  return returned;
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
  calculatedParam = (-1 * (p.a * d.randPoint.x + p.b * d.randPoint.y + p.c * d.randPoint.x + p.d)) / (p.a * d.dir.x + p.b * d.dir.y + p.c * d.dir.z);

  return calculatedParam;
}

point* intersectPlanHalfLine(cartesianPlan p, halfLine d){
  float calculatedParam = calculParam(p, d);
  point* returnedPoint = malloc(sizeof(point));

  if(d.min == true && d.param <= calculatedParam){
    returnedPoint->x = d.randPoint.x + d.dir.x*calculatedParam;
    returnedPoint->y = d.randPoint.y + d.dir.y*calculatedParam;
    returnedPoint->z = d.randPoint.z + d.dir.z*calculatedParam;
    return returnedPoint;
  } else if(d.min == false && d.param >= calculatedParam){
    returnedPoint->x = d.randPoint.x + d.dir.x*calculatedParam;
    returnedPoint->y = d.randPoint.y + d.dir.y*calculatedParam;
    returnedPoint->z = d.randPoint.z + d.dir.z*calculatedParam;
    return returnedPoint;
  }
  else{
    return NULL;
  }



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

cartesianPlan definePlan(vector dir1, vector dir2, point insidePoint){
  cartesianPlan plan;
  plan.a = dir1.y * dir2.z - dir1.z * dir2.y;
  plan.b = dir1.z * dir2.x - dir1.x * dir2.z;
  plan.c = dir1.x * dir2.y - dir1.y * dir2.x;
  plan.d = -(plan.a * insidePoint.x + plan.b * insidePoint.y + plan.c * insidePoint.z);
  return plan;
}

cartesianPlan polygonPlan(polygon inputPolygon){
  int vertexNbr;
  vector vectorDir1;
  vector vectorDir2;
  cartesianPlan polygonPlan;

  vertexNbr = inputPolygon.pointNbr;
  if(vertexNbr > 2){
    vectorDir1 = setVector(*inputPolygon.vertex, *(inputPolygon.vertex+1));
    vectorDir2 = setVector(*inputPolygon.vertex, *(inputPolygon.vertex+2));
    polygonPlan = definePlan(vectorDir1, vectorDir2, *inputPolygon.vertex);
  }
  else{
    polygonPlan.a = 0;
    polygonPlan.b = 0;
    polygonPlan.c = 0;
    polygonPlan.d = 0;
  }
  return polygonPlan;
}

bool isRayInpolygon(polygon inputPolygon, halfLine ray){
  cartesianPlan planOfPolygon;
  cartesianPlan normalPlan;
  int vertexNbr;
  point* intersection;
  vector planVector;
  vector normalVector;
  bool* symbol;

  vertexNbr = inputPolygon.pointNbr;
  symbol = malloc(vertexNbr*sizeof(bool));
  planOfPolygon = polygonPlan(inputPolygon);

  if(planOfPolygon.a == 0 && planOfPolygon.b == 0 && planOfPolygon.c == 0 && planOfPolygon.d == 0){
    return false;
  }

  intersection = intersectPlanHalfLine(planOfPolygon, ray);
  normalVector.x = planOfPolygon.a;
  normalVector.y = planOfPolygon.b;
  normalVector.z = planOfPolygon.c;
  float result;

  for(int i = 0; i < vertexNbr; i++){
    if(i == vertexNbr-1){
      planVector = setVector(*(inputPolygon.vertex), *(inputPolygon.vertex+i));
    }
    else{
      planVector = setVector(*(inputPolygon.vertex+i), *(inputPolygon.vertex+i+1));
    }
    normalPlan = definePlan(planVector, normalVector, *(inputPolygon.vertex+i));
    result = normalPlan.a*intersection->x + normalPlan.b*intersection->y + normalPlan.c*intersection->z + normalPlan.d;
    if(result >= 0){
      *(symbol+i) = true;
    }
    else{
      *(symbol+i) = false;
    }
  }

  for(int i = 0; i < vertexNbr; i++){
    if(*(symbol+i) != *(symbol+i+1)){
      return false;
    }
  }

  return true;;

}

float distancePoints(point a, point b){
  float distance;
  distance = pow(pow(b.x-a.x,2) + pow(b.y-a.y,2) + pow(b.z-a.z,2),0.5);
  return distance;
}

point* intersectSpheroideHalfLine(spheroide inputSphere, halfLine ray, point distancePoint){
  double discriminant;
  double a;
  double b;
  double c;
  float t1;
  float t2;
  float distance1;
  float distance2;
  point* returnedPoint1 = malloc(sizeof(point));
  point* returnedPoint2 = malloc(sizeof(point));
  //
  // a = pow(ray.dir.x,2) + pow(ray.dir.y,2) + pow(ray.dir.z,2);
  // b = 2*(spheroide.a * ray.point.x + spheroide.b * ray.point.y + spheroide.c* ray.point.z);
  // b -= 2*(spheroide.a * ray.dir.x + spheroide.b * ray.dir.y + spheroide.c * ray.dir.z);
  // c = pow(ray.point.x,2) + pow(ray.point.y,2) + pow(ray.point.z,2);
  // c += pow(spheroide.a,2) + pow(spheroide.b,2) + pow(spheroide.c,2) - pow(spheroide.d,2);
  // c -= 2*(spheroide.a * ray.point.x + spheroide.b * ray.point.y + spheroide.c * ray.point.z);



    // a = pow(ray.dir.x,2) + pow(ray.dir.y,2) + pow(ray.dir.z,2);
    // b = 2 * (ray.dir.x * (ray.randPoint.x - inputSphere.a) + ray.dir.y * (ray.randPoint.y - inputSphere.b) + ray.dir.z * (ray.randPoint.z - inputSphere.c));
    // c = (pow(ray.randPoint.x - inputSphere.a, 2) + pow(ray.randPoint.y - inputSphere.b, 2) + pow(ray.randPoint.z - inputSphere.c, 2)) - (inputSphere.d);
    a = inputSphere.a * pow(ray.dir.x,2) + inputSphere.b * pow(ray.dir.y,2) + inputSphere.c * pow(ray.dir.z,2);
    a += 2*inputSphere.d* ray.dir.y *ray.dir.z + 2*inputSphere.e * ray.dir.x * ray.dir.z + 2*inputSphere.f * ray.dir.x*ray.dir.y;

    b = 2*inputSphere.a * (ray.randPoint.x-inputSphere.k) * ray.dir.x + 2*inputSphere.b * (ray.randPoint.y-inputSphere.l) * ray.dir.y +  2*inputSphere.c * (ray.randPoint.z-inputSphere.m) * ray.dir.z;
    b += 2*inputSphere.d*(ray.randPoint.y - inputSphere.l) * ray.dir.z + 2*inputSphere.d*(ray.randPoint.z - inputSphere.m) * ray.dir.y + 2*inputSphere.e*(ray.randPoint.x -inputSphere.k)*ray.dir.z + 2*inputSphere.e*(ray.randPoint.z -inputSphere.m)*ray.dir.x;
    b += 2*inputSphere.f*(ray.randPoint.x - inputSphere.k)*ray.dir.y +  2*inputSphere.f*(ray.randPoint.y - inputSphere.l)*ray.dir.x + inputSphere.g * ray.dir.x + inputSphere.h * ray.dir.y + inputSphere.i*ray.dir.z;

    c = inputSphere.a*pow(ray.randPoint.x - inputSphere.k,2) + inputSphere.b*pow(ray.randPoint.y - inputSphere.l,2) + inputSphere.c*pow(ray.randPoint.z - inputSphere.m,2) + 2*inputSphere.d*(ray.randPoint.y - inputSphere.l)*(ray.randPoint.z - inputSphere.m);
    c += 2*inputSphere.e*(ray.randPoint.x - inputSphere.k)*(ray.randPoint.z - inputSphere.m) + 2*inputSphere.f*(ray.randPoint.x - inputSphere.k)*(ray.randPoint.y - inputSphere.l) + inputSphere.g*(ray.randPoint.x - inputSphere.k) + inputSphere.h*(ray.randPoint.y - inputSphere.l);
    c += inputSphere.i*(ray.randPoint.z - inputSphere.m) - inputSphere.j;



  discriminant = pow(b,2) - 4*a*c;
if(discriminant >= 0){
    t1 = (-b-sqrt(discriminant))/(2*a);
    t2 = (-b+sqrt(discriminant))/(2*a);
  } else{
    return NULL;
  }

  if(ray.min == true && ray.param <= t1){
    returnedPoint1->x = (ray.randPoint.x + ray.dir.x*t1);
    returnedPoint1->y = (ray.randPoint.y + ray.dir.y*t1);
    returnedPoint1->z = (ray.randPoint.z + ray.dir.z*t1);
  } else if(ray.min == false && ray.param >= t1){
    returnedPoint1->x = (ray.randPoint.x + ray.dir.x*t1);
    returnedPoint1->y = (ray.randPoint.y + ray.dir.y*t1);
    returnedPoint1->z = (ray.randPoint.z + ray.dir.z*t1);
  }

  if(ray.min == true && ray.param <= t2){
    returnedPoint2->x = (ray.randPoint.x + ray.dir.x*t2);
    returnedPoint2->y = (ray.randPoint.y + ray.dir.y*t2);
    returnedPoint2->z = (ray.randPoint.z + ray.dir.z*t2);
  } else if(ray.min == false && ray.param >= t2){
    returnedPoint2->x = (ray.randPoint.x + ray.dir.x*t2);
    returnedPoint2->y = (ray.randPoint.y + ray.dir.y*t2);
    returnedPoint2->z = (ray.randPoint.z + ray.dir.z*t2);
  }
  else{
    return NULL;
  }

  distance1 = distancePoints(distancePoint, *returnedPoint1);
  distance2 = distancePoints(distancePoint, *returnedPoint2);
  if(distance1 < distance2){
    return returnedPoint1;
  }
  else{
    return returnedPoint2;
  }
}

bool comparePoints(point a, point b){
  if(trunc(a.x-b.x)==0 && trunc(a.y-b.y)==0 && trunc(a.z-b.z) == 0){
    return true;
  }
  return false;
}

point intersectSolidHalfLine(solid *po, halfLine ray, point camera){
  point *pointsTab = (point*)malloc(sizeof(point));
  point closestPoint;
  int *distanceTab = (int*)malloc(sizeof(int));
  for(int i = 0; i<po->nbPolygon; i++){
    if(isRayInpolygon(*(po->tabPolygon+i), ray) == true){
      cartesianPlan plan = polygonPlan(*(po->tabPolygon+i));
      *(pointsTab + i) = * intersectPlanHalfLine(plan, ray);
      *(distanceTab + i) = distancePoints(*(pointsTab + i), camera);
    }
    else{
      *(distanceTab + i) = 999999999;
    }
  }
  int distMin = 999999;
  for(int j = 0; j<po->nbPolygon; j++){
    if(distMin > *(distanceTab + j)){
      distMin = *(distanceTab + j);
    }
    j++;
  }
  int count;
  for(int k = 0; k<po->nbPolygon; k++){
    if(distMin == *(distanceTab + k)){
      count = k;
    }
    k++;
  }
  int l = 0;
  while(pointsTab != NULL){
    if(l == count){
      closestPoint = *(pointsTab + l);
    }
    l++;
  }
  return closestPoint;
}
