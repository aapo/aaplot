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

double p1[2],p2[2],p3[2],p4[1],p5[1];
p1[0]=2;
p1[1]=-5;
addRCurveWithP(0,&butterfly,p1,1.5,0.01,-5,15,"butterfly 1",0.2,1,0.2);

p2[0]=6;
p2[1]=-1;
addRCurveWithP(0,&butterfly,p2,1.5,0.01,-5,15,"butterfly 2",0.5,1,0.5);

p3[0]=-6;
p3[1]=3;
addRCurveWithP(0,&butterfly,p3,1.5,0.01,-5,15,"butterfly 3",0.8,1,0.8);

p4[0]=-2;
p4[1]=7;
addRCurveWithP(0,&butterfly,p4,1.5,0.01,-5,15,"butterfly 4",1,1,1);

/*
addRCurve(0,&cubic1,1.5,0.01,-2,2,"cubic1",0,0,1);
addRCurve(0,&astroid,1.5,0.01,-3,3,"astroid",0,1,1);
addRCurve(0,&cardioid,1.5,0.01,0,6,"cardioid",1,1,1);
addRCurve(0,&ellipse,1.5,0.01,0,8,"ellipse",1,0,0);
addRCurve(0,&cruciform,1.5,0.01,-20,20,"cruciform",1,1,0);


addRCurve(0,&deltoid,1.5,0.01,-5,5,"deltoid",0,0,1);
addRCurve(0,&epicycloid,1.5,0.01,-5,5,"epicycloid",0,0,1);

addRCurve(0,&epitrochoid,1.5,0.01,-5,5,"epitrochoid",0,0,1);


addRCurve(0,&hypocycloid,1.5,0.01,-5,5,"hypocycloid",0,0,1);
addRCurve(0,&aapocycloid,1.5,0.01,-5,5,"aa-pocycloid",0,1,1);

addRCurve(0,&kappa_curve,1.5,0.01,-5,5,"kappa_curve",0,1,1);

addRCurve(0,&nephroid,1.5,0.01,-5,5,"nephroid",1,0,1);
addRCurve(0,&nephroid2,1.5,0.01,-5,5,"nephroid2",0,1,0);

addRCurve(0,&serpentine,1.5,0.01,-5,5,"serpentine",0,1,0);

addRCurve(0,&torusknot,10.0,0.05,0,17,"torusknot",0,1,0);


addRCurve(0,&butterfly,1,0.001,0,17,"butterfly",1,1,0);

addRCurve(0,&rose,1.5,0.01,-5,5,"rose",1,0,0);
addRCurve(0,&archimedes,1.5,0.01,-50,50,"archimedes",1,1,0);

addRCurve(0,&twisted,1.5,0.01,-50,50,"twisted",1,1,0);
addRCurve(0,&lemniscate,1.5,0.01,0,6.5,"lemniscate",1,1,0);

addRCurve(0,&viviani,1.5,0.01,-2*M_PI,2*M_PI,"viviani",1,1,0);
addRCurve(0,&baseball,1.5,0.01,0,4*M_PI,"baseball",1,1,0);
*/

/* //fast way to test some points
double x,y,z;
granny(1,&x,&y,&z);
printf("%lf,%lf,%lf\n",x,y,z);
return 0;
*/


drawAll(); /*suoritus pysahtyy tahan kunnes kaikki graafiset ikkunat on suljettu*/
return 0;
}


