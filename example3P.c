/*
Curve R->R^3.
(There are no R->R^2 curves)
With curve, we must define stepping like we do with functions. Additional we must explicitly define the range of parameter. (first and last value)

This example draws two ellipses with different parameters
*/
#include "aaplot.c"

/*Even this is plane-object, we must set all x,y,z */
void ellipse(double t, double *x, double *y, double *z, double *p) {
*x= p[0] * cos(t);
*y= p[1] * sin(t);
*z= 0;
}


int main(){
double p1[2];
p1[0]=5.5;
p1[1]=2.3;


/*window_number, curve, parameters, step, first_value, last_value,title*/
addRCurveWithP(0,&ellipse,p1,0.01,0,2*M_PI,"ellipse 1");


/*We can't use same array with another function */
double p2[3];
p2[0]= 1.4;
p2[1]= 2.3;

addRCurveWithP(0,&ellipse,p2,0.01,0,2*M_PI,"ellipse 2");

drawAll();
return 0;
}


