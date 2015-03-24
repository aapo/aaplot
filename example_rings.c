/*
Three rings. If anyone is removed, two are not 'linked'.
But all together are 'linked'.
*/
#include "aaplot.h"


void ring(double u, double *x, double *y, double *z, double *p) {
double r = (pow(3,0.5)/3); /* radius */
*x= cos(u) +p[0];
*y= sin(u) + r/p[1];
*z= cos(3*u) / 3.0;
}


int main(void)
{
/*BLACK background*/
/*
default_background_color[0]=0.0;
default_background_color[1]=0.0;
default_background_color[2]=0.0;
default_size=9.0;
*/

double p1[2],p2[2],p3[2];
p1[0]= 0,   p1[1]= 1;
p2[0]= 0.5, p2[1]=-2;
p3[0]=-0.5, p3[1]=-2;

addRCurveWithP(0,&ring,p1,0.01,0,2*M_PI,"ring1");
addRCurveWithP(0,&ring,p2,0.01,0,2*M_PI,"ring2");
addRCurveWithP(0,&ring,p3,0.01,0,2*M_PI,"ring3");

drawAll(); 
return 0;
}


