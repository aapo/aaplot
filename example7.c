/*Uses three windows
window 0: f
window 1: g
window 2: derivate of f and g
*/
#include "aaplot.h"

double f(double x) {
return sin(x);
}

double g(double x) {
return x*x;
}

/*derivate of f */
double Df(double x) {
return cos(x);
}

/*derivate of g */
double Dg(double x) {
return 2*x;
}

int main() { 
addRFunction(0,&f,0.01,"sin x");
addRFunction(1,&g,0.01,"x*x");

default_lower_bounds[0] = -1.0;
default_lower_bounds[1] = -5.0;
default_lower_bounds[2] = -3.0;

default_upper_bounds[0] = 5.0;
default_upper_bounds[1] = 1.0;
default_upper_bounds[2] = 3.0;


addRFunction(2,&Df,0.01,"D(sin x)");
addRFunction(2,&Dg,0.01,"D(x*x)");

drawAll();
return 0;
}
