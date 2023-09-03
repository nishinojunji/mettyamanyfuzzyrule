/* fuzzy.h : fuzzy library */
/* Junji Nishino 2019/1/4 */

#define ZENKEN_LIM 10
#define POINT_LIM 10
#define RULE_LIM 900

/* element with grade */
typedef struct {
  double x; /* discourse */
  double g; /* grade on x */
} Point;

/* linked multi point fuzzy membership function*/
typedef struct {
  int pointnum;
  Point p[POINT_LIM];
} Fuzzyset;

typedef struct {
  int zenken_num;
  Fuzzyset zenken[ZENKEN_LIM];
  double koken;
} Fuzzyrule;

typedef struct {
  int rulenum;
  Fuzzyrule fr[RULE_LIM];
} Fuzzysystem;


/* prototypes of functions */

Fuzzyset fuzzyset_init();
Fuzzyset fuzzyset_addpoint(Fuzzyset a, double x, double g);
double fuzzyset_grade(Fuzzyset f, double x);
Fuzzyset fuzzyset_triangle(double l, double m, double r);

Fuzzyrule fuzzyrule_init();
Fuzzyrule fuzzyrule_set_zenkennum(Fuzzyrule r, int num);
Fuzzyrule fuzzyrule_set_zenken(Fuzzyrule r, Fuzzyset a[]);
Fuzzyrule fuzzyrule_set_koken(Fuzzyrule r, double koken);

Fuzzysystem fuzzysystem_init();
Fuzzysystem fuzzysystem_add(Fuzzysystem s, Fuzzyrule r);
double fuzzyrule_match(Fuzzyrule fr, double x[]);
double fuzzyreasoning(Fuzzysystem s, double x[]);



double fuzzy_min(double a, double b);
double fuzzy_max(double a, double b);

