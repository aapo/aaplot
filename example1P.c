/*
one R->R function with parameters.
Same function but different parameters.
*/

#include "aaplot.h"

double my_func(double x, double *p) {
return p[0]*x*x + p[1]*x + p[2];
}

int main(){
double p1[3];
p1[0]=-2.4;
p1[1]=-3.1;
p1[2]= 1.8;

/*window_number, function,parameters, x_step, title*/
addRFunctionWithP(0,&my_func,p1,0.001,"parabola1");

/*We can't use same array with another function */
double p2[3];
p2[0]=-2.4;
p2[1]=-3.1;
p2[2]= 3.8;
addRFunctionWithP(0,&my_func,p2,0.001,"parabola2");

drawAll(); 
return 0;
}
