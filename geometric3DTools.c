#include <math.h>

vecteur qFoisVecteur(int k, vecteur u){
  u.x = k * u.x;
  u.y = k * u.y;
  u.z = k * u.z;
  return u;
}

vecteur additionVecteurs(vecteur u, vecteur v){
  vecteur w;
  w.x = u.x + v.x;
  w.y = u.y + v.y;
  w.z = u.z + v.z;
  return w;
}

vecteur soustractionVecteurs(vecteur u, vecteur v){
  vecteur w;
  w.x = u.x - v.x;
  w.y = u.y - v.y;
  w.z = u.z - v.z;
  return w;
}

float normeVecteur(vecteur u){
  return sqrt(pow(u.x, 2) + pow(u.y, 2) + pow(u.z, 2));
}

vecteur scalaireVecteurs(vecteur u, vecteur v){
  return 1 / 2 * (normeVecteur(u) + normeVecteur(v) - normeVecteur(soustractionVecteur(v, u)));
}

vecteur produitVectoriel(vecteur u, vecteur v){
  vecteur w;
  w.x = u.y * v.z - u.z * v.y;
  w.y = u.z * v.x - u.x * v.z;
  w.z = u.x * v.y - u.y * v.x;
  return w;
}
