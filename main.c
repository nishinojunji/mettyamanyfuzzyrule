/* fuzzy program test main */

#include<stdio.h>
#include "fuzzy.h"

#define ZENKEN_NUM 1

int main(){
  Fuzzyset a[ZENKEN_NUM];
  Fuzzyrule r;
  Fuzzysystem s;

  r = fuzzyrule_init();
  r = fuzzyrule_set_zenkennum(r, ZENKEN_NUM);

  s = fuzzysystem_init();

  a[0] = fuzzyset_triangle(0.0, 1.0, 2.0);
  r = fuzzyrule_set_zenken(r, a);
  r = fuzzyrule_set_koken(r, 1.0);
  s = fuzzysystem_add(s, r);


  a[0] = fuzzyset_triangle(1.0, 2.0, 3.0);
  r = fuzzyrule_set_zenken(r, a);
  r = fuzzyrule_set_koken(r, 2.0);
  s = fuzzysystem_add(s, r);

  a[0] = fuzzyset_triangle(2.0, 3.0, 4.0);
  r = fuzzyrule_set_zenken(r, a);
  r = fuzzyrule_set_koken(r, 0.5);
  s = fuzzysystem_add(s, r);

  double input[1], result;
  int x;
  for(x=0; x<=20; x++){
    input[0] = 1.0 + x/10.0; /* 1.0 <= input[0] <= 3.0 */
    result = fuzzyreasoning(s, input);

    printf("%lf, %lf\n", input[0], result);
  }

}
