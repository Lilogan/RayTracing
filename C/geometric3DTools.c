#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#include "geometric3DTools.h"

#define pi 3.1415923565

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

solid setSolid(int nbPolygon , polygon* tabPolygon){
  solid sol;
  sol.nbPolygon = nbPolygon;
  sol.tabPolygon = tabPolygon;
  return sol;
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
  s.m = m;

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
  return u.x*v.x+u.y*v.y+u.z*v.z;
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
  if(p.a != 0 || p.b != 0 || p.c != 0){
    calculatedParam = (-1 * (p.a * d.randPoint.x + p.b * d.randPoint.y + p.c * d.randPoint.z + p.d)) / (p.a * d.dir.x + p.b * d.dir.y + p.c * d.dir.z);
    return calculatedParam;
  }
  return 0;

}

point* intersectPlanHalfLine(cartesianPlan p, halfLine d){
  float calculatedParam = calculParam(p, d);
  point* returnedPoint = malloc(sizeof(point));
  //printf("%f \n",calculatedParam);
  if(d.min == true && d.param < calculatedParam){
    returnedPoint->x = d.randPoint.x + d.dir.x*calculatedParam;
    returnedPoint->y = d.randPoint.y + d.dir.y*calculatedParam;
    returnedPoint->z = d.randPoint.z + d.dir.z*calculatedParam;
    return returnedPoint;
  } else if(d.min == false && d.param > calculatedParam){
    returnedPoint->x = d.randPoint.x + d.dir.x*calculatedParam;
    returnedPoint->y = d.randPoint.y + d.dir.y*calculatedParam;
    returnedPoint->z = d.randPoint.z + d.dir.z*calculatedParam;
    return returnedPoint;
  }
  else{
    return NULL;
  }



}

vector normalPlan(cartesianPlan p, vector incident){
  vector normal;
  normal.x = p.a;
  normal.y = p.b;
  normal.z = p.c;
  if(scalarVectors(normal, incident) < 0){
    normal = qTimeVector(-1,normal);
  }
  return normal;
}

vector reflectPlan(halfLine i, cartesianPlan p){
  vector incident;
  vector reflected;
  vector normalVec;
  float incidentNorm;
  float normalNorm;
  incident = i.dir;
  incidentNorm = pow(normVector(incident),-1);
  normalVec = normalPlan(p, incident);
  normalNorm = pow(normVector(normalVec),-1);

  float cosinus = cosVector(incident, normalVec);

  if(cosinus >= -1 && cosinus <= 1){
    reflected = addVectors(normalizeVector(incident), qTimeVector(2*cosinus,normalizeVector(normalVec)));
    //printf("%f %f %f\n",reflected.x, reflected.y, reflected.z);
  }
  else{
    reflected.x = 0;
    reflected.y = 0;
    reflected.z = 0;
  }
  //printf("%f %f %f\n",reflected.x, reflected.y, reflected.z);
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
  //printf("     StartPlan\n");
  int vertexNbr;
  vector vectorDir1;
  vector vectorDir2;
  point* vertex = inputPolygon.vertex;
  //printf("     vertex\n");
  cartesianPlan polygonPlan;
  vertexNbr = inputPolygon.pointNbr;
  // printf("     nbrVertex : %d\n", vertexNbr);
  if(vertexNbr > 2){
  //printf(" %f-%f-%f  | %f-%f-%f\n", vertex[0].x,vertex[0].y,vertex[0].z,vertex[1].x,vertex[1].y,vertex[1].z);
    vectorDir1 = setVector(vertex[0], vertex[1]);
  //  printf("       Dir1\n");
    vectorDir2 = setVector(vertex[0], vertex[2]);
  //  printf("       Dir2\n");
    polygonPlan = definePlan(vectorDir1, vectorDir2, vertex[0]);
    printf("\n");
  //printf("%d\n",err);
  }
  else{
  //  printf("     < 2\n");
    polygonPlan.a = 0;
    polygonPlan.b = 0;
    polygonPlan.c = 0;
    polygonPlan.d = 0;
  }
  return polygonPlan;
}

bool isInPlan(point inputPoint, cartesianPlan inputPlan){
  float pointX = inputPoint.x;
  float pointY = inputPoint.y;
  float pointZ = inputPoint.z;
  float paramA = inputPlan.a;
  float paramB = inputPlan.b;
  float paramC = inputPlan.c;
  float paramD = inputPlan.d;
  vector one;
  vector two;
  double angle;

  if(trunc(paramA*pointX+paramB*pointY+paramC*pointZ+paramD) == 0){
      return true;
  }
  return false;
}

point* intersectPolygon(polygon inputPolygon, halfLine ray){
  vector A;
  vector B;
  double angle;
  cartesianPlan planPolygon;
  point *intersect;
  int nbrVertex;
  planPolygon = polygonPlan(inputPolygon);
  intersect = intersectPlanHalfLine(planPolygon, ray);
  nbrVertex = inputPolygon.pointNbr;
  angle = 0;
  for(int i = 0; i<nbrVertex; i++){
    if(intersect == NULL){
      return NULL;
    }
    A = setVector(*intersect, inputPolygon.vertex[i]);
    if(i == nbrVertex-1){
      B = setVector(*intersect, inputPolygon.vertex[0]);
    }
    else{
      B =  setVector(*intersect, inputPolygon.vertex[i+1]);
    }
    angle += acos(cosVector(A,B))*180/pi;
  }
  //printf("%lf\n",angle);
  if((angle-5) <= 360 && (angle+5)>=360){
    //printf("touché polygon\n");
    return intersect;
  }
  //printf("raté polygon\n");
  return NULL;

}

float distancePoints(point a, point b){
  float distance;

  distance = sqrt(pow(b.x-a.x,2) + pow(b.y-a.y,2) + pow(b.z-a.z,2));

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
  if(trunc(a.x-b.x)==0 && trunc(a.y-b.y)==0 &&trunc (a.z-b.z) == 0){
    return true;
  }
  return false;
}

point* intersectSolidHalfLine(solid sol, halfLine ray, point distancePoint){
  int nbPoly = sol.nbPolygon;
//  printf("nb poly :%d\n",nbPoly);
  point* intersect = NULL;
  point* pointV = NULL;
  float distV = -1;
  float distPt = -1;
  for(int i = 0; i<nbPoly; i++){
    distPt = -1;
    //printf("  01\n");
    intersect = intersectPolygon(sol.tabPolygon[i], ray);
  //  printf("  %p\n", intersect);
    if(intersect != NULL){
      distPt = distancePoints(*intersect, distancePoint);
    }

    if(intersect != NULL && distPt > distV){
      distV = distPt;
      pointV = intersect;
    }
  }

  if(distV == -1){
    return NULL;
  }

  return pointV;
}

polygon closestPolygon(solid sol, halfLine ray){
  int nbPoly = sol.nbPolygon;
  point* intersect;
  point* pointV;
  float distV = -1;
  float distPt = -1;
  int rang = -1;
  polygon closest;
  for(int i = 0; i<nbPoly; i++){
    distPt = -1;
    intersect = intersectPolygon(sol.tabPolygon[i], ray);
    if(intersect != NULL){
      distPt = distancePoints(*intersect, ray.randPoint);
    }

    if(intersect != NULL && distPt > distV){
      distV = distPt;
      pointV = intersect;
      closest = sol.tabPolygon[i];
    }
  }
  return closest;
}

cartesianPlan whichFaceIsPoint(solid inputSolid, point inputPoint){
  int nbrPoly = inputSolid.nbPolygon;
  polygon *tabPoly = inputSolid.tabPolygon;
  cartesianPlan currentPlan;
  cartesianPlan returned;

  for (int i = 0; i < nbrPoly; i++) {
    currentPlan = polygonPlan(tabPoly[i]);
    if(isInPlan(inputPoint,currentPlan)){
      returned = currentPlan;
    }
  }

  return currentPlan;
}

vector normalSpheroide(spheroide inputSpheroide, point normalPoint){
  /*float x = 2*inputSpheroide.a*normalPoint.x + inputSpheroide.e*normalPoint.z +
  inputSpheroide.f*normalPoint.y + inputSpheroide.g;
  float y = 2*inputSpheroide.b*normalPoint.y + inputSpheroide.d*normalPoint.z +
  inputSpheroide.f*normalPoint.x + inputSpheroide.h;
  float z = 2*inputSpheroide.c*normalPoint.z + inputSpheroide.d*normalPoint.y +
  inputSpheroide.e*normalPoint.x + inputSpheroide.i;*/
  float x = normalPoint.x;
  float y = normalPoint.y;
  float z = normalPoint.z;
  vector normal = setVector(setPoint(inputSpheroide.k,inputSpheroide.l,inputSpheroide.m),setPoint(x,y,z));

  return normal;
}

vector normalizeVector(vector inputVector){
  float x = inputVector.x/normVector(inputVector);
  float y = inputVector.y/normVector(inputVector);
  float z = inputVector.z/normVector(inputVector);
  vector normalize = setVector(setPoint(0,0,0),setPoint(x,y,z));
  return normalize;
}

double cosVector(vector first, vector second){
  return scalarVectors(first,second)/(normVector(first)*normVector(second));
}

point translate(point pt, vector vec){
  point returned;
  returned.x = pt.x + vec.x;
  returned.y = pt.y + vec.y;
  returned.z = pt.z + vec.z;
  return returned;
}
 vector normalSolid(solid inputSolid, halfLine incident, point intersect){
   vector normal;
   cartesianPlan plan  = whichFaceIsPoint(inputSolid,intersect);
   normal = normalPlan(plan,incident.dir);
   return normal;
 }
