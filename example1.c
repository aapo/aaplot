/*Simple example:
one R->R function */

#include "aaplot.h"

double my_func(double x) {
return 2*x*x + 4*x - 2;
}

int main(){
//you can change global settings
default_lower_x_limit = -2.0;
default_upper_x_limit = 8.0;

default_lower_y_limit = -3.0;
default_upper_y_limit = 7.0;

default_lower_z_limit = -4.0;
default_upper_z_limit = 6.0;

default_x_grid=1.2;
default_y_grid=1.3;
default_z_grid=0.7;

default_coordplane[0]=0;
default_coordplane[1]=1;
default_coordplane[2]=1;

/*window_number, function, x_step, title*/
addRFunction(0,&my_func,0.001,"parabola");


drawAll(); /*main programs pauses till all windows are closed*/

return 0;
}

