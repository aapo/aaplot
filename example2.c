/*
One R2->R function.
f(x,z)=y */
#include "aaplot.c"


double surface(double x,double z) {
return sin(2*x)*cos(2*z);
}


int main(void)    {
/*window_number, function, x_step,z_step, title */
addR2Function(0,&surface,0.05,0.05,"sin 2x * cos 2z");

drawAll();
return 0;
}


