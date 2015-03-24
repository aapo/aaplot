/*
Draws two plot-sets from files. (Aalto Vase)
First file has 26 x,y points.
Second file has 100 x,y points.

Additional we make two arrays, so one means x-coordinates and the other y-coordinates.
Then we draw these points.
*/

#include "aaplot.c"


int main(){
/*window_number, file_name, plot_size, title*/
addTableDataFile(0,"aalto.dat" ,3, "aalto26"); 
addTableDataFile(0,"aalto2.dat",2, "aalto100");


/*-Arrays---------------*/
/*Dynamical arrays*/
int number_of_points = 10;
double *x,*y;
x= (double *) malloc(number_of_points*sizeof(double));
y= (double *) malloc(number_of_points*sizeof(double));

/*Compile-time arrays*/
/*
#define number_of_points 10
double x[number_of_points];
double y[number_of_points]; 
*/

/*Some values*/
int i=0;
for (i=0;i<number_of_points;i++)
  {
  x[i]=i*cos(i);
  y[i]=i*sin(i);
  }

/*window_number, total, x,y, plot_size, title*/
addTableDataArrays(0,number_of_points,x,y,5, "some_test_data");

drawAll();
return 0;
}
