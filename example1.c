/*Simple example:
one R->R function */

#include "aaplot.h"

double my_func(double x) {
return 2*x*x + 4*x - 2;
}

int main(){
/*window_number, function, x_step, title*/
addRFunction(0,&my_func,0.001,"parabola");

/*we can take the return value and change attributes and behaving of function*/
int id_number = addRFunction(0,&my_func,0.001,"parabola2");
int new_direction=4;   /* look values in aaplot.h*/
changeDirection(id_number, new_direction);

drawAll(); /*main programs pauses till all windows are closed*/

return 0;
}

