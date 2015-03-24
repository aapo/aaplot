/*piirtaa parametrisoituja kayria
Aina on pakko olla kolme arvoa, jonkun voi toki laittaa vakioksi. */
#include "aaplot.c"

void helix(double alfa, double *x, double *y, double *z) {
double a=2;    /*1. pikku-akseli */
double b=3;    /*2. pikku-akseli */
double c=0.2;  /*kierteisyys*/
*x= a*cos (alfa);
*y= b*sin (alfa);
*z= c*alfa;
}

void cubic(double t, double *x, double *y, double *z) {
*x= t*t -1;
*y= t * (t*t -1);
*z= 0;
}

void astroid(double t, double *x, double *y, double *z) {
*x= 4*pow(cos(t),3);
*y= 4*pow(sin(t),3);
*z= 1;
}

void cardioid(double t, double *x, double *y, double *z) {
double r=1;
*x= 2*r * (cos(t) -0.5*cos(2*t));
*y= 2*r * (sin(t) -0.5*sin(2*t));
*z= -1;
}

void ellipse(double t, double *x, double *y, double *z) {
double a=1;
double b=2;
*x= a * cos(t);
*y= 2;
*z= b * sin(t);
}

void kappa_curve(double t, double *x, double *y, double *z) {
double a=1;
*x= a * cos(t) * 1.0/tan(t);
*y= a * cos (t);
*z= 0;
}

void cruciform(double t, double *x, double *y, double *z) {
*x= (t*t -2*t +5) / (t*t -2*t -3);
*y= (t*t -2*t +5) / (2*t -2);
*z= -3;
}

void deltoid(double t, double *x, double *y, double *z) {
double a=1;
*x= 2*a * cos(t) + a* cos(2*t);
*y= 2*a * sin(t) - a* sin(2*t);
*z= -3;
}

void epicycloid(double t, double *x, double *y, double *z) {
double k=3.0; /*numbers of 'leafs' */
*x= (k+1) * (cos(t) - (cos ((k+1)*t))/(k+1));
*y= (k+1) * (sin(t) - (sin ((k+1)*t))/(k+1));
*z= 0;
}

void hypocycloid(double t, double *x, double *y, double *z) {
double k=5.0; /*numbers of 'cusps' */
*x= (k-1) * (cos(t) + (cos ((k-1)*t)/(k-1)));
*y= (k-1) * (sin(t) - (sin ((k-1)*t)/(k-1)));
*z= 0;
}

/*some version of hypocycloid*/
void aapocycloid(double t, double *x, double *y, double *z) {
double k=3.0; /*numbers of 'leafs' -2*/
double s=1.65; /*scale */
*x= s* (k-1) * (cos(t) + (cos ((k+1)*t))/(k-1));
*y= s* (k-1) * (sin(t) - (sin ((k+1)*t))/(k-1));
*z= 0;
}

void epitrochoid(double t, double *x, double *y, double *z) {
double R=3.0; /*Big cirle */
double r=1.0; /*little cirle */
double d=0.5; /* distance of circles*/
*x= (R+r) * cos(t) - d*cos (t*(R+r)/(r));
*y= (R+r) * sin(t) - d*sin (t*(R+r)/(r));
*z= 0;
}

void nephroid(double t, double *x, double *y, double *z) {
*x= 3*cos(t)+cos(3*t);
*y= 3*sin(t)+sin(3*t);
*z=1;
}

void nephroid2(double t, double *x, double *y, double *z) {
*x= 3*cos(t)-cos(3*t);
*y= 3*sin(t)-sin(3*t);
*z=-1;
}

void serpentine(double t, double *x, double *y, double *z) {
double a=1;
double b=1;
*x= a * 1.0 / tan(t);
*y= b * sin(t)*cos(t);
*z= 0;
}

/*if you use bigger p and q values, you need bigger alfa range*/
void torusknot(double t, double *x, double *y, double *z) {
double p=2;
double q=3;
*x= (2+cos(q*t/p)) * cos (t);
*y= (2+cos(q*t/p)) * sin (t);
*z= sin (q*t/p);
}

void butterfly(double u, double *x, double *y, double *z) {
*x = cos(u) * (exp(cos(u)) - 2 * cos(4 * u) - pow(sin(u / 12),5.0));
*y = sin(u) * (exp(cos(u)) - 2 * cos(4 * u) - pow(sin(u / 12),5.0));
*z = fabs(*y) / 2;
}

void rose(double t, double *x, double *y, double *z) {
double n=7;  /*petals (n odd) or 2n petals (n even)*/
*x= cos(t) * cos(n*t);
*y= sin(t) * cos(n*t);
*z= 1;
}

void spirals(double t, double *x, double *y, double *z) {
double n=1; /*n=1:archimedes. n=2:fermats. n=-1:hyperbolic. n=-2:Lituus*/
double r = 0.3; /*radius */
*x= r* pow(t,(1/n)) * cos(t);
*y= r* pow(t,(1/n)) * sin(t);
*z= 1;
}

void twisted(double t, double *x, double *y, double *z) {
*x = t;
*y = t*t;
*z = t*t*t;
}

void lemniscate(double t, double *x, double *y, double *z) {
double a=1;
*x = (a * cos(t)) / (1+ pow(sin(t),2));
*y = (a * cos(t) * sin(t)) / (1+ pow(sin(t),2));
*z = 0;
}

void viviani(double t, double *x, double *y, double *z) {
*x = 1 + cos(t);
*y = sin(t);
*z = 2 * sin(t/2);
}

void baseball(double t, double *x, double *y, double *z) {
double a=0.4;
double r=3;
*x = r* sin(M_PI/2 - (M_PI/2 - a) * cos(t)) * cos(t/2 + a* sin(2 *t));
*y = r* sin(M_PI/2 - (M_PI/2 - a) * cos(t)) * sin(t/2 + a* sin(2 *t));
*z = r* cos(M_PI/2 - (M_PI/2 - a) * cos(t));
}

void granny(double u, double *x, double *y, double *z) {
double s =0.02; /*scale*/
*x = s*( -22 * cos(u)   - 128 * sin(u)   - 44 * cos(3*u) - 78 * sin(3*u) );
*y = s*( -10 * cos(2*u) -  27 * sin(2*u) + 38 * cos(4*u) + 46 * sin(4*u) );
*z = s*(  70 * cos(3*u) -  40 * sin(3*u) );
}

int main(void)
{
/*BLACK background*/
default_background_color[0]=0.0;
default_background_color[1]=0.0;
default_background_color[2]=0.0;

#ifdef pois
addRCurve   (0        /* window number        */
            ,&helix   /* curve                */
            ,2.0      /* size of points       */
            ,0.1      /* stepping of alfa     */
            ,-5.0    /* starting alfa        */
            ,5.0     /* ending alfa          */
            ,"helix"  /* title of function    */
            ,1,0,1);  /* colors in RGB [0,1]  */
#endif
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


addRCurve(0,&granny,1.5,0.01,0,2*M_PI,"granny_knot",1,1,0);

/* //fast way to test some points
double x,y,z;
granny(1,&x,&y,&z);
printf("%lf,%lf,%lf\n",x,y,z);
return 0;
*/


drawAll(); /*suoritus pysahtyy tahan kunnes kaikki graafiset ikkunat on suljettu*/
return 0;
}


