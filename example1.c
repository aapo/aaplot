/*Simple example:
one R->R function */

#include "aaplot.c"

double my_func(double x) {
return 2*x*x + 4*x - 2;
}

int main(){
/*window_number, function, plot_size, x_step, title*/
addRFunction(0,&my_func,1.0,0.001,"parabola");

drawAll(); /*main programs pauses till all windows are closed*/
return 0;
}

