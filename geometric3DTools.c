#include <math.h>

vecteur qTimeVector(int k, vecteur u){
  u.x = k * u.x;
  u.y = k * u.y;
  u.z = k * u.z;
  return u;
}

vecteur addVectors(vecteur u, vecteur v){
  vecteur w;
  w.x = u.x + v.x;
  w.y = u.y + v.y;
  w.z = u.z + v.z;
  return w;
}
substractVectors
vecteur substractVectors(vecteur u, vecteur v){
  vecteur w;
  w.x = u.x - v.x;
  w.y = u.y - v.y;
  w.z = u.z - v.z;
  return w;
}

float normVector(vecteur u){
  return sqrt(pow(u.x, 2) + pow(u.y, 2) + pow(u.z, 2));
}

vecteur scalarVectors(vecteur u, vecteur v){
  return 1 / 2 * (normeVecteur(u) + normeVecteur(v) - normeVecteur(soustractionVecteur(v, u)));
}

vecteur productVector(vecteur u, vecteur v){
  vecteur w;
  w.x = u.y * v.z - u.z * v.y;
  w.y = u.z * v.x - u.x * v.z;
  w.z = u.x * v.y - u.y * v.x;
  return w;
}
