#include <math.h>

typedef struct droite_{
	float t;
	int x;
	int y;
	int z;
}droite;//à vérifier

typedef struct fonction_ {
  int a;
  int b;
  int c;
  int d;
} fonction;

typedef struct point_ {
  int x;
  int y;
  int z;
} point;

typedef struct plan_ {
  int a;
  int b;
  int c;
  int d;
} plan;

typedef struct vecteur_ {
  int x;
  int y;
  int z;
} vecteur;

vecteur qFoisVecteur(int k, vecteur u);

vecteur additionVecteurs(vecteur u, vecteur v);

vecteur soustractionVecteurs(vecteur u, vecteur v);

vecteur scalaireVecteurs(vecteur u, vecteur v);

float normeVecteur(vecteur u);

vecteur produitVectoriel(vecteur u, vecteur v);

point intersection(plan p, droite d);

vecteur reflechi(vecteur i, plan p);

vecteur refracte(vecteur i, plan p);

plan premierEltRencontre(point obs, vecteur ray);

vecteur normale(plan p);
