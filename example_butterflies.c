/*four parameterized butterflies*/
#include "aaplot.c"

void butterfly(double u, double *x, double *y, double *z, double *p) {
*x = p[1] + cos(u) * (exp(cos(u)) - 2 * cos(4 * u) - pow(sin(u / 12),5.0));
*z = sin(u) * (exp(cos(u)) - 2 * cos(4 * u) - pow(sin(u / 12),5.0));
*y = fabs(*z) / p[0];
}


int main(void)
{
/*BLACK background*/
default_background_color[0]=0.0;
default_background_color[1]=0.0;
default_background_color[2]=0.0;

double p1[2],p2[2],p3[2],p4[1];
p1[0]=2;
p1[1]=-6;
addRCurveWithP(0,&butterfly,p1,1.5,0.01,-5,15,"butterfly 1");

p2[0]=6;
p2[1]=-2;
addRCurveWithP(0,&butterfly,p2,1.5,0.01,-5,15,"butterfly 2");

p3[0]=-6;
p3[1]=2;
addRCurveWithP(0,&butterfly,p3,1.5,0.01,-5,15,"butterfly 3");

p4[0]=-2;
p4[1]=6;
addRCurveWithP(0,&butterfly,p4,1.5,0.01,-5,15,"butterfly 4");


drawAll(); 
return 0;
}


