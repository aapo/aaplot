/*example:
one R->R function 
and how to get user clicked points*/

#include "aaplot.c"

double my_func(double x) {
return 2*x*x + 4*x - 2;
}

int main(){
/*window_number, function, x_step, title*/

addRFunction(0,&my_func,0.001,"parabola");

drawAll(); /*main programs pauses till all windows are closed*/

int n,i;
double *points = getClickedPointsFromWindow(0,&n);

printf("Selected points:\n");
for (i=0;i<2*n;i=i+2)
  {
  printf("(%lf,%lf)\n",points[i],points[i+1]);
  }

return 0;
}
