/*
One R2->R function. with parameters.
Same function but different parameters.

f(x,z)=y */
#include "aaplot.c"


double surface(double x,double z, double *p) {
return sin(p[0]*x) * cos(p[1]*z) + p[2];
}

int main() {
double p1[3];
p1[0]=2.4;
p1[1]=1.1;
p1[2]=2.1;

/*window_number, function, plot_size,x_step,z_step, title */
addR2FunctionWithP(0,&surface,p1,2.0,0.01,0.01,"sin a*x * cos b*z");

/*We can't use same array with another function */
double p2[3];
p2[0]= 1.4;
p2[1]= 3.1;
p2[2]=-2.8;

addR2FunctionWithP(0,&surface,p2,2.0,0.01,0.01,"sin a*x * cos b*z");


drawAll();
return 0;
}


