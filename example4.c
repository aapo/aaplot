/*
Curve R2->R^3.
Now we have two stepping values.

*/
#include "aaplot.h"


void circle3(double t, double u, double *x, double *y, double *z) {
double r=1; /* radius */
*x= r * cos(t);
*y= u;
*z= r * sin(t);
}



int main(){
/*window_number,curve,  step_A, step_B, first_value_A, last_value_A, first_value_B, last_value_B, title*/
addR2Curve(0,&circle3,0.01,0.2,0,2*M_PI,-2,2,"tube");

drawAll();
return 0;
}
