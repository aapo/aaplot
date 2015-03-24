/*four parameterized butterflies*/
#include "aaplot.h"

void butterfly(double u, double *x, double *y, double *z, double *p) {
*x = p[1] + cos(u) * (exp(cos(u)) - 2 * cos(4 * u) - pow(sin(u / 12),5.0));
*z =        sin(u) * (exp(cos(u)) - 2 * cos(4 * u) - pow(sin(u / 12),5.0));
*y = fabs(*z) / p[0];
}


int main()
{
/*BLACK background*/
default_background_color[0]=0.0;
default_background_color[1]=0.0;
default_background_color[2]=0.0;
default_size=1.5;

 default_window_width =800;
 default_window_height=800;

default_coordplane[0]=0;
default_coordplane[1]=0;
default_coordplane[2]=0;

double p1[2],p2[2],p3[2],p4[2];
p1[0]=2;
p1[1]=-6;
addRCurveWithP(0,&butterfly,p1,0.001,0.175,6.105,"butterfly 1");



drawAll();
return 0;
}


