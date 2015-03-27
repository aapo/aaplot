/*
Two windows with different background colors
*/


#include "aaplot.h"

double f(double x) {
return x*x;
}

double f2(double x,double z) {
return sin(2*x)*cos(2*z);
}

double fB(double x,double z,double *p) {
return 3+sin(p[0]*x)*cos(p[1]*z);
}


void c(double t, double *x, double *y, double *z) {
double a=0.4;
double r=3;
*x = r* sin(M_PI/2 - (M_PI/2 - a) * cos(t)) * cos(t/2 + a* sin(2 *t));
*y = r* sin(M_PI/2 - (M_PI/2 - a) * cos(t)) * sin(t/2 + a* sin(2 *t));
*z = r* cos(M_PI/2 - (M_PI/2 - a) * cos(t));
}

void c2(double t, double *x, double *y, double *z,double *p) {
double R=3.0; /*Big cirle */
double r=1.0; /*little cirle */
double d=p[0]; /* distance of circles*/
*x= (R+r) * cos(t) - d*cos (t*(R+r)/(r));
*y= (R+r) * sin(t) - d*sin (t*(R+r)/(r));
*z= 0;
}


double g(double x,double *para) {
return x*para[0];
}


int main(void)
{
srand (41872);
double p[1],p2[1],p3[2],p4[1],p5[1];


default_background_color[0]=1.0;
default_background_color[1]=0.0;
default_background_color[2]=0.0;
/* This is the first time when window0 is called, so it will be initialized
   and it gets  background color */
addRFunction(0          /* window number        */
            ,&f         /* function             */
            ,0.1        /* stepping of x        */
            ,"x * x");  /* title of function    */


/* Change default backgound color*/
default_background_color[0]=0.0;
default_background_color[1]=1.0;
default_background_color[2]=1.0;

/* This is the first time when window1 is called, so it will be initialized
   and it gets  background color */
addR2Function(1,                      /* window number        */
              &f2,                    /* function             */
              0.05,                   /* stepping of x        */
              0.05,                   /* stepping of z        */
              "x*z");                 /* title of function    */


/*cant use same array in different instance*/

p[0]=2,p2[0]=3;
addRFunctionWithP(0,&g,p ,0.01,"2x");
addRFunctionWithP(0,&g,p2,0.01,"3x");

p3[0]=2,p3[1]=0.4;
addR2FunctionWithP(0,&fB,p3,0.05,0.05,"3+sin(p[0]*x)*cos(p[1]*z)");

addRCurve(0,&c,0.01,-5,15,"baseball");

p4[0]=0.3;
p5[0]=0.6;


addRCurveWithP(0,&c2,p4,0.01,-5,15,"epicycloid1");
addRCurveWithP(0,&c2,p5,0.01,-5,15,"epicycloid2");


default_lower_bounds[0] = -10.0;
default_lower_bounds[1] = -10.0;
default_lower_bounds[2] = -4.0;

default_lower_bounds[0] = 10.0;
default_lower_bounds[1] = 10.0;
default_lower_bounds[2] = 4.0;


drawAll(); /* Window(s) are shown and execution waits here*/
printf("Quitted\n");
return 0;
}


