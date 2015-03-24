/*
One R2->R function. with parameters.

f(x,y)=z */
#include "aaplot.h"


double surface(double x,double y, double *p) {
return sin(p[0]*x) * cos(p[1]*y) + p[2];
}

int main() {
double p1[3];
p1[0]=2.4;
p1[1]=1.1;
p1[2]=2.1;

/*window_number, function,x_step,z_step, title */
addR2FunctionWithP(0,&surface,p1,0.05,0.05,"sin a*x * cos b*y");

/*We can't use same array with another function */
double p2[3];
p2[0]= 1.4;
p2[1]= 3.1;
p2[2]=-2.8;

addR2FunctionWithP(0,&surface,p2,0.05,0.05,"sin a*x * cos b*y");


drawAll();
return 0;
}


