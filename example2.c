/*
One R2->R function.
default direction is f(x,y)=z 
look example1.c to change direction*/
#include "aaplot.h"

double surface(double x,double y) {
return sin(2*x)*cos(2*y);
}


int main(void)    {
/*window_number, function, step_1,step_2, title */
addR2Function(0,&surface,0.05,0.05,"sin 2x * cos 2z");

drawAll();
return 0;
}



