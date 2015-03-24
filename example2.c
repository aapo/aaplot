/*
One R2->R function.
f(x,z)=y */
#include "aaplot.c"


double surface(double x,double z) {
return sin(2*x)*cos(2*z);
}


int main(void)    {
/*window_number, function, plot_size,x_step,z_step, title */
addR2Function(0,&surface,2.0,0.01,0.01,"sin 2x * cos 2z");

drawAll();
return 0;
}


