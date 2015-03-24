/*
Draws two plot-sets from files. (Aalto Vase)
First file has 26 x,y points.
Second file has 100 x,y points.

Additional we make three arrays. First means x-coordinates the second y-coordinates and last z-coordinates.
We can make 2d-table. The last value is default_2dtable_thirdvalue like when loaded 2d table from file.
*/

#include "aaplot.h"

int main(){
default_size=3.0;
default_2dtable_thirdvalue=-1.23;

/*window_number, file_name, title*/
addTableDataFile(0,"aalto2.dat" , "aalto_100");


default_size=13.0;
default_2dtable_thirdvalue=0.43;

/*window_number, file_name, title*/
addTableDataFile(0,"aalto.dat" , "aalto_26");


/*-Arrays---------------*/
/*Dynamical arrays*/
int number_of_points = 10;
double *x,*y,*z;
x= malloc(number_of_points*sizeof(double));
y= malloc(number_of_points*sizeof(double));
z= malloc(number_of_points*sizeof(double));

/*Compile-time arrays*/
/*
#define number_of_points 10
double x[number_of_points];
double y[number_of_points];
double z[number_of_points];
*/

/*Some values*/
int i=0;
for (i=0;i<number_of_points;i++)
  {
  x[i]=i*cos(i);
  y[i]=i*sin(i);
  }

default_size=5.0;
/*window_number, total, x,y, title*/
addTableDataArrays(0,number_of_points,x,y, "some 2d data");




/*3d table, use same x and y than 2d*/
for (i=0;i<number_of_points;i++)
  {
  z[i]=i*0.5;
  }

/*window_number, total, x,y,z, title*/
addTableDataArrays3d(0,number_of_points,x,y,z, "some 3d data");


drawAll();
return 0;
}
