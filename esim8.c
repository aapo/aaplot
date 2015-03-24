#include "aaplot.c"

//const double r=pow(3,2);//pow(3,0.5)/3;
#define r (pow(3,0.5)/3)
/*aina pakko olla kolme arvoa.
jonkun voi toki laittaa vakioksi. */

void ring1(double u, double *x, double *y, double *z) {
*x= cos(u);
*y= sin(u) + r;
*z= cos(3*u) / 3.0;
}

void ring2(double u, double *x, double *y, double *z) {
*x= cos(u) + 0.5;
*y= sin(u) - r/2.0;
*z= cos(3*u) / 3.0;
}

void ring3(double u, double *x, double *y, double *z) {
*x= cos(u) - 0.5;
*y= sin(u) - r/2;
*z= cos(3*u) / 3.0;
}


int main(void)
{
/*BLACK background*/
default_background_color[0]=0.0;
default_background_color[1]=0.0;
default_background_color[2]=0.0;


addRCurve(0,&ring1,9.0,0.01,0,2*M_PI,"ring1",1,0,0);
addRCurve(0,&ring2,9.0,0.01,0,2*M_PI,"ring2",0,1,0);
addRCurve(0,&ring3,9.0,0.01,0,2*M_PI,"ring3",0,0,1);

drawAll(); /*suoritus pysahtyy tahan kunnes kaikki graafiset ikkunat on suljettu*/
return 0;
}


