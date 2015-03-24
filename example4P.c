/*
Curve R2->R^3, with parameters

This example draws two ellipses with different parameters
*/
#include "aaplot.h"

void circles(double t, double u, double *x, double *y, double *z, double *p) {
double r=p[0]; /* radius */
*x= p[1] + r * cos(t);
*y= u;
*z= r * sin(t);
}


int main(){

double p1[2];
p1[0]= 1.0;
p1[1]= 3.0;
/*window_number,curve, parameters, step_A, step_B, first_value_A, last_value_A, first_value_B, last_value_B, title*/
addR2CurveWithP(0,&circles,p1,0.01,0.3,0,2*M_PI,0,3,"tube1");


double p2[2];
p2[0]= 2.0;
p2[1]= -3.0;
addR2CurveWithP(0,&circles,p2,0.01,0.5,0,2*M_PI,-2,2,"tube2");

drawAll();
return 0;
}
