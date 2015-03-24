/*
Draws two plot-sets from files. (Aalto Vase)
First file has 26 x,y points.
Second file has 100 x,y points.

Additional we make two arrays, so one means x-coordinates and the other y-coordinates.
Then we draw these points.
*/

#include "aaplot.h"


int main(){
/*window_number, file_name, title*/
default_size=13.0;

addTableDataFile(0,"aalto.dat" , "aalto26"); 
addTableDataFile(0,"aalto2.dat", "aalto100");


/*-Arrays---------------*/
/*Dynamical arrays*/
int number_of_points = 10;
double *x,*y;
x= malloc(number_of_points*sizeof(double));
y= malloc(number_of_points*sizeof(double));

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

/* default_size=5.0; */
/*window_number, total, x,y, title*/
addTableDataArrays(0,number_of_points,x,y, "some_test_data");

drawAll();
return 0;
}
