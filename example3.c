/*
Curve R->R^3.
(There are no R->R^2 curves)
With curve, we must define stepping like we do with functions. Additional we must explicitly define the range of parameter. (first and last value)

This example draws
 -circle 
 -baseball curve
*/
#include "aaplot.c"

/*Even this is plane-object, we must set all x,y,z */
void circle(double t, double *x, double *y, double *z) {
double r=1; /* radius */
*x= r * cos(t);
*y= 2;
*z= r * sin(t);
}


void baseball(double t, double *x, double *y, double *z) {
double a=0.4; /*some constant*/
double r=3;  /* radius */
*x = r* sin(M_PI/2 - (M_PI/2 - a) * cos(t)) * cos(t/2 + a* sin(2 *t));
*y = r* sin(M_PI/2 - (M_PI/2 - a) * cos(t)) * sin(t/2 + a* sin(2 *t));
*z = r* cos(M_PI/2 - (M_PI/2 - a) * cos(t));
}

int main(){
/*window_number,curve, plot_size, step, first_value, last_value,title*/
addRCurve(0,&circle,1.5,0.01,0,2*M_PI,"Circle");
addRCurve(0,&baseball,1.5,0.01,-5,15,"Baseball curve");

/*Note about range
with cirle, it is trivial that we draw [0,2PI].
with baseball-curve, we must 
 -calculate it
 -test it (empiric)
 -overstate it
*/

drawAll();
return 0;
}


