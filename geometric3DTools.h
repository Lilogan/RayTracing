#include <math.h>

typedef struct point_ {
  //A = (x,y,z)
  float x;
  float y;
  float z;
} point;

typedef struct planCartesien_ {
  //ax+by+cs+d=0
  float a;
  float b;
  float c;
  float d;
} planCartesien;

typedef struct planParametrique_{
  vecteur dir1;
  vecteur dir2;
  point point;
} planParametrique;

typedef struct vecteur_ {
  //A= (x,y,z)
  float x;
  float y;
  float z;
} vecteur;

typedef struct droite_{
	vecteur dir;
  point point;
}droite;

typedef struct demiDroite_{
	vecteur dir;
  point point;
  float paramMin;
}demiDroite;

typedef struct polygone_{
  int nbrePoint;
  point* sommets;
}

vecteur qFoisVecteur(int k, vecteur u);

vecteur additionVecteurs(vecteur u, vecteur v);

vecteur soustractionVecteurs(vecteur u, vecteur v);

vecteur scalaireVecteurs(vecteur u, vecteur v);

float normeVecteur(vecteur u);

vecteur produitVectoriel(vecteur u, vecteur v);

point intersection(planCartesien p, droite d);

vecteur reflechi(vecteur i, planCartesien p);

vecteur refracte(vecteur i, planCartesien p);

planCartesien premierEltRencontre(point obs, vecteur ray);

vecteur normale(planCartesien p);
