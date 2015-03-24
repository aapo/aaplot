/*
Draws one big 3d-model. It has over 100k points.
(originally obj-format, points only)

Saucepan by Gilles Tran
http://www.oyonale.com/modeles.php?lang=en&page=41
Creative Commons License By Attribution
http://creativecommons.org/licenses/by/3.0/
*/

#include "aaplot.h"

int main(){
default_size=2.0;

/** clipping area*/
default_lower_bounds[0] = -30.0;
default_upper_bounds[0] = 20.0;

default_lower_bounds[1] = -5.0;
default_upper_bounds[1] = 15.0;

default_lower_bounds[2] = -15.0;
default_upper_bounds[2] = 15.0;

/** plazement of the camera*/
default_camera[0]=-5;
default_target[0]=-5;

default_camera[1]=10;
default_target[1]=10;

default_camera[2]=20;
default_target[2]=10;

/** all coordinate plane will be visible*/
default_coordplane[0]=1;
default_coordplane[1]=1;
default_coordplane[2]=1;

/*window_number, file_name, title*/
addTableDataFile(0,"saucepan.dat" , "Pan");


drawAll();
return 0;
}
