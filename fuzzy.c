/* fuzzy.c : fuzzy library */
/* Junji Nishino 2019/1/4 */

#include<stdio.h>
#include "fuzzy.h"

Fuzzyset fuzzyset_init(){
  Fuzzyset a;
  a.pointnum=0;
  return a;
}

Fuzzyset fuzzyset_addpoint(Fuzzyset a, double x, double g){
  if(a.pointnum >= POINT_LIM){
    printf("fuzzyset_addpoint : overflow\n");
    return a;
  }

  a.p[a.pointnum].x = x;
  a.p[a.pointnum].g = g;

  a.pointnum++;

  return a;
}

double fuzzyset_grade(Fuzzyset f, double x){
  int i;
  
  i=0;
  while(1){
    if(i> f.pointnum) break;
    if(x < f.p[i].x) break;
    i++;
  }

  if(i<=0){
    return 0.0;
  }
  if(i>f.pointnum){
    return 0.0;
  }

  /* f.p[i-1].x <= x < f.p[i] */

  double g;

  g = (f.p[i].g - f.p[i-1].g) * (x - f.p[i].x) / (f.p[i].x - f.p[i-1].x) + f.p[i].g;

  return g;

}

Fuzzyset fuzzyset_triangle(double l, double m, double r){
  Fuzzyset a;
  a = fuzzyset_init();
  a = fuzzyset_addpoint(a, l, 0.0);
  a = fuzzyset_addpoint(a, m, 1.0);
  a = fuzzyset_addpoint(a, r, 0.0);

  return a;
}




Fuzzyrule fuzzyrule_init(){
  Fuzzyrule r;
  
  r.zenken_num = 0;

  return r;
}


Fuzzyrule fuzzyrule_set_zenkennum(Fuzzyrule r, int num){
  r.zenken_num = num;
  return r;
}

Fuzzyrule fuzzyrule_set_zenken(Fuzzyrule r, Fuzzyset a[]){
  int i;

  for(i=0; i<r.zenken_num; i++){
    r.zenken[i] = a[i];
  }

  return r;
}

Fuzzyrule fuzzyrule_set_koken(Fuzzyrule r, double koken){
  r.koken = koken;

  return r;
}




Fuzzysystem fuzzysystem_init(){
  Fuzzysystem s;

  s.rulenum = 0;
  return s;
}

Fuzzysystem fuzzysystem_add(Fuzzysystem s, Fuzzyrule r){

  if(s.rulenum >= RULE_LIM){
    printf("fuzzysystem_add : over flow\n");
    return s;
  }

  s.fr[s.rulenum] = r;
  s.rulenum++;

  return s;
}

double fuzzyrule_match(Fuzzyrule fr, double x[]){
  int dim, i;
  double match, g;

  dim = fr.zenken_num;

  match = 1.0;
  for(i=0; i<dim; i++){
    g = fuzzyset_grade(fr.zenken[i], x[i]);
    match = fuzzy_min(match, g);
  }

  return match;

}

/* fuzzy inference */
double fuzzyreasoning(Fuzzysystem s, double x[]){
  int i;
  double e, nu, de;

  nu = de = 0.0;
  for(i=0; i<s.rulenum; i++){
    e = fuzzyrule_match(s.fr[i], x);
    nu += e * s.fr[i].koken;
    de += e;
  }

  if(de == 0.0){
    printf("fuzzyreasoning : underflow err\n");
    return 0.0;
  }

  double result;
  result = nu/de;
  return result;
}



double fuzzy_min(double a, double b){
  if(a<b) return a;
  return b;
}

double fuzzy_max(double a, double b){
  if(a>b) return a;
  return b;
}
