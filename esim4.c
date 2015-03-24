/*
Funktio R2->R.
Todella isolla askelluksella.
 */
#include "aaplot.c"

double f(double x,double z) {
return sin(x)*cos(z);
}


void c(double t, double *x, double *y, double *z) {
double a=0.4;
double r=3;
*x = r* sin(M_PI/2 - (M_PI/2 - a) * cos(t)) * cos(t/2 + a* sin(2 *t));
*y = 3 + r* sin(M_PI/2 - (M_PI/2 - a) * cos(t)) * sin(t/2 + a* sin(2 *t));
*z = r* cos(M_PI/2 - (M_PI/2 - a) * cos(t));
}

int main(void)    {

addR2Function(0,                     /* window number        */
              &f,                    /* function             */
              2.0,                   /* size of points       */
              0.1,                   /* stepping of x        */
              0.1,                   /* stepping of z        */
              "sin x * cos z",            /* title of function    */
              1,0,0);                /* colors in RGB [0,1]  */

addRCurve(0,&c,1.5,0.01,-5,15,"Baseball curve",0,0,1);


lower_z_limit = -5.0;
upper_z_limit = 5.0; 

lower_y_limit = -1.0;
upper_y_limit = 6.0;

lower_x_limit = -5.0;
upper_x_limit = 5.0;

drawAll();
return 0;
}


