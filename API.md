#How to use aaplot

# Basic #
Write c-file, include aaplot
```
#include "aaplot.h"
```
Compile
```
gcc -lpng -lXpm -lGL
```

-lpng means libpng, which is used to screenshooting. (aaplot can be compiled without it)

-lXpm means libXpm, which is used to change application-icon (aaplot can be compiled without it)

-lGL are mandatory

# API for version 0.6 #
There are some default-globals, e.g, limits of the _drawing cube_
```
double default_lower_bounds[3] = {-10.0, -5.0, -3.0};
double default_upper_bounds[3] = { 10.0,  5.0,  3.0};
```
You can change the values in your code. When you make new window (add some element to it) it gets **current** defaults.

## addRFunction ##
int addRFunction(int win,double (`*`func\_ptr)(double), double step, char `*`title)

win
> Windows number. First window is 0.

func\_ptr
> Pointer to function, which is like
> > double some\_function(double x) {return x+1;}

step

> Stepping of x. Let say first value of x is A, then second value is A+step. And all values are A+(step `*` n), where n is integer.

title
> Title of function. Will be written in 'legend' in same color than function itself. (legend is info box, which lists all functions)

returning int
> ID\_number of just added function. Its properties are changed with this id number. This id is very own. Even functions are in different windows they can't have same id number. Additional function can't have same id number which is used any table (and vica versa)

### Example ###
```
#include "aaplot.h"
double f(double x) {
return x*x;
}

int main()
{
addRFunction(0,&f,0.01,"x * x");
drawAll(); 
return 0;
}

```

## addR2Function ##
int addR2Function(int win,double (`*`func\_ptr)(double), double x\_step, double z\_step, char `*`title)

win
> Windows number. First window is 0.

func\_ptr
> Pointer to function, which is like
> > double some\_function(double x,double z) {return x+z+1;}

x\_step

> Stepping of x. Let say first value of x is A, then second value is A+step. And all values are A+(step `*` n), where n is integer.

z\_step
> Stepping of z.

title
> Title of function. Will be written in 'legend' in same color than function itself. (legend is info box, which lists all functions)

returning int
> ID\_number of just added function. Its properties are changed with this id number. This id is very own. Even functions are in different windows they can't have same id number. Additional function can't have same id number which is used any table (and vica versa)


### Example ###
```
#include "aaplot.h"
double g(double x,double z) {
return x*z;
}

int main()
{
addR2Function(0,&f,0.01,0.01,"x * z");
drawAll(); 
return 0;
}

```


## addRCurve ##
int addRCurve(int win,void (`*`curve\_ptr)(double,double`*`,double`*`,double`*`), double step, double lower, double upper,char `*`title)

win
> Windows number. First window is 0.

curve\_ptr
> Pointer to curve, which is like
> > double some\_function(double t, double `*`x, double `*`y, double `*`z)  {`*`x=t;  `*`y=t;  `*`z=t;}

step

> Stepping of t. Let say first value of x is A, then second value is A+step. And all values are A+(step `*` n), where n is integer.

lower
> First value of t.

upper
> Last value of t.

title
> Title of curve. Will be written in 'legend' in same color than function itself. (legend is info box, which lists all functions)

returning int
> ID\_number of just added curve. Its properties are changed with this id number. This id is very own. Even curves/functions are in different windows they can't have same id number. Additional curves can't have same id number which is used any table (and vica versa)


### Example ###
```
#include "aaplot.h"
void circle(double t, double *x, double *y, double *z) {
*x= cos(t);
*y= sin(t);
*z= 0;
}

int main(){
addRCurve(0,&circle,0.01, 0, 2*M_PI,"Circle");
drawAll();
return 0;
}


```



## addR2Curve ##
int addR2Curve(int win,void (`*`curve\_ptr)(double,double,double`*`,double`*`,double`*`), double step, double step\_1, double lowerA, double upperA, double lowerB, double upperB, char `*`title)

win
> Windows number. First window is 0.

curve\_ptr
> Pointer to curve, which is like
> > double some\_function(double t, double u, double `*`x, double `*`y, double `*`z)  {`*`x=t;  `*`y=t;  `*`z=t;}

step

> Stepping of t. Let say first value of x is A, then second value is A+step. And all values are A+(step `*` n), where n is integer.

step\_1
> Stepping of u.

lowerA
> First value of t.

upperA
> Last value of t.

lowerB
> First value of u.

upperB
> Last value of u.

title
> Title of curve. Will be written in 'legend' in same color than function itself. (legend is info box, which lists all functions)

returning int
> ID\_number of just added curve. Its properties are changed with this id number. This id is very own. Even curves/functions are in different windows they can't have same id number. Additional curves can't have same id number which is used any table (and vica versa)


### Example ###
```
#include "aaplot.h"
void circle3(double t, double u, double *x, double *y, double *z) {
double r=u; /* radius */
*x= r * cos(t);
*y= 2;
*z= r * sin(t);
}


void circle(double t, double *x, double *y, double *z) {
*x= cos(t);
*y= sin(t);
*z= 0;
}

int main(){
addR2Curve(0,&circle3,0.01,0.5,0,2*M_PI,0,2,"circles");
drawAll();
return 0;
}


```

## Tables ##
## addTableDataFile ##
int addTableDataFile(int win,char `*`filename , `*`title)

win
> Windows number. First window is 0.

filename
> Name of the file. Fileformat is like
```
 26 2
 0.0 -4.0
 1.0 -3.6
 2.0 -3.6
 3.0 -4.0
 3.7 -3.7
 4.0 -3.0
 3.6 -1.0
 3.6  0.3
 4.0  1.0
 4.0  2.0
 2.8  4.0
 2.3  4.3
 1.0  4.0
-1.0  3.3
-2.7  3.5
-3.8  3.2
-4.0  2.2
-3.5  1.2
-3.7  0.0
-4.0 -1.2
-4.1 -3.0
-3.8 -3.7
-3.0 -4.0
-2.0 -3.6
-1.0 -3.6
 0.0 -4.0
```
> Or like this
```
 6 3
 0.0 -4.0 -3.0
 1.0 -3.6 -2.0
 2.0 -3.6 -1.0
 3.0 -4.0 0.0
 3.7 -3.7 1.0
 4.0 -3.0 2.0
```
> First is number of points. Actually how many points is readed, if there are too less numbers, rest comes 'randomly'. Second is how many dimension: 2 or 3 dimension. All of values are doubles.

title
> Title of point set. Will be written in 'legend' in same color than points. (legend is info box, which lists all functions)

returning int
> ID\_number of just added function. Its properties are changed with this id number. This id is very own. Even functions are in different windows they can't have same id number. Additional function can't have same id number which is used any table (and vica versa)

**Note**
> There are global (double) named _default\_2dtable\_thirdvalue_, which is the third value of two-dimensional tables.


## addTableDataArrays ##
int addTableDataArrays(int win,int number\_of\_points,double **x,double**x,  char `*`title)

win
> Windows number. First window is 0.

number\_of\_points
> How many points there are or you want to draw,

x,y
> Can be double[.md](.md). First point is (x[0](0.md),y[0](0.md)) and point number i is (x[i](i.md),y[i](i.md)).

title
> Title of point set. Will be written in 'legend' in same color than points itself. (legend is info box, which lists all functions)

returning int
> ID\_number of just added function. Its properties are changed with this id number. This id is very own. Even functions are in different windows they can't have same id number. Additional function can't have same id number which is used any table (and vica versa)

### Example ###
```
#include "aaplot.h"
int main(){
/* you must have aalto.dat */
addTableDataFile(0,"aalto.dat" , "aalto26");
drawAll();
```

### Example2 ###
```
#include "aaplot.h"
int main(){
int number_of_points = 10;
double *x,*y;
x= malloc(number_of_points*sizeof(double));
y= malloc(number_of_points*sizeof(double));

/*Some values*/
int i=0;
for (i=0;i<number_of_points;i++)
  {
  x[i]=i*cos(i);
  y[i]=i*sin(i);
  }
addTableDataArrays(0,number_of_points,x,y, "some_test_data");
drawAll();
```


### Example3 ###
```
#include "aaplot.h"
int main(){
#define number_of_points 10
double x[number_of_points];
double y[number_of_points];

/*Some values*/
int i=0;
for (i=0;i<number_of_points;i++)
  {
  x[i]=i*cos(i);
  y[i]=i*sin(i);
  }
addTableDataArrays(0,number_of_points,x,y, "some_test_data");
drawAll();
```

## Parameterized functions ##
int addRFunctionWithP(int win,double (`*`func\_ptr)(double,double`*`),double `*`para, double step, char `*`title)

int addR2FunctionWithP(int win,double (`*`func\_ptr)(double,double,double`*`),double `*`para, double x\_step, double z\_step, char `*`title)

int addRCurveWithP(int win,void (`*`curve\_ptr)(double,double`*`,double`*`,double`*`,double`*`), double `*`para, double step, double lower, double upper,char `*`title)

int addR2CurveWithP(int win,void (`*`curve\_ptr)(double,double,double`*`,double`*`,double`*`,double`*`), double `*`para, double step, double step\_1,double lowerA, double upperA, double lowerB, double upperB, char `*`title)

func\_ptr / curve\_ptr
> is now pointing different kind of function. There are one double`*` more

para
> array of parameters

### Example ###
```
#include "aaplot.h"
void circle_with_radius(double t, double *x, double *y, double *z, double *p) {
*x= p[0] * cos(t);
*y= p[0] * sin(t);
*z= 0;
}

int main(){
double p1[1];
p1[0]= 1.25; 

addRCurveWithP(0,&circle_with_radius,p1,0.01, 0, 2*M_PI,"Circle");
drawAll();
return 0;
}


```

# Changing values #
Anything that returns id number to you is called entity and can be target of attribute-changing-functions.

## changeEntityPlotSize ##
void changeEntityPlotSize (int id, float size)

id
> id number of function, curve or table

size
> new plot/point size

## changeEntityColor ##
void changeEntityColor(int id, float red, float green, float blue)

id
> id number of function, curve or table

red,green,blue
> all in range [0,1]. They together is RGB-value. RGB-color-system is additive, which means it behaves like mixing light:
```
  0,0,0 = BLACK
  1,0,0 = RED
  0,1,0 = GREEN
  0,0,1 = BLUE
  1,1,1 = WHITE
```

## toggleHidden ##
void toggleHidden(int id)

id
> id number of function, curve or table

## changeDirection ##

void changeDirection(int id, int d)

id
> id number of function, curve or table

d
> New direction:
|d \ type |[R2](https://code.google.com/p/aaplot/source/detail?r=2)->R        |3dTable   | R->R      |2dTable|
|:--------|:------------------------------------------------------------------|:---------|:----------|:------|
|1 |f(x,y)=z     |xyz   |f(x)=y      |XY|
|2 |f(x,z)=y     |xzy   |f(x)=z      |XZ|
|3 |f(y,x)=z     |yxz   |f(y)=x      |YX|
|4 |f(y,z)=x     |yzx   |f(y)=z      |YZ|
|5 |f(z,x)=y     |zxy   |f(z)=x      |ZX|
|6 |f(z,y)=x     |zyx   |f(z)=y      |ZY|

## changeEntityStepping0 ##
Not for tables.

void changeEntityStepping0(int id, double step\_0)

id
> id number of function or curve

step\_0
> New value of first stepping.

## changeEntityStepping1 ##
Not for tables.

Changing step\_1 of R->R function means nothing

void changeEntityStepping1(int id, double step\_1)

id
> id number of function or curve

step\_1
> New value of second stepping.

## changeEntityTitle ##
void changeEntityTitle(int id, char **title)**

id
> id number of function, curve or table

title
> New title of entity.


example
```
int id = addRCurveWithP(0,&circle_with_radius,p1,0.01, 0, 2*M_PI,"Circle");

changeEntityColor(id, 0.5, 0.5, 0.5);
changeEntityPlotSize(id, 3.5);
changeEntityStepping0(id, 0.0001);
changeEntityTitle(id, "Circle!");
```


# After GUI #
When you close last graphical window, the main program continues and can ask if user choosed (clicked) some points.

## getClickedPointsFromWindow ##
double `*`getClickedPointsFromWindow(int win, int `*`n)

win
> Asked window.

n
> Returns how many clicked points.

returning double[.md](.md)
> First and second values is coordinates of the first point. Generally: `point j = (table[i],table[i+1]), i=2j, j<=n.`

NOTE:
> Size of returned array is 2\*n.

### Example ###
```
#include "aaplot.h"

double my_func(double x) {
return 2*x*x + 4*x - 2;
}

int main(){
addRFunction(0,&my_func,0.001,"parabola");
drawAll(); /*main programs pauses till all windows are closed*/

int n;
double *points = getClickedPointsFromWindow(0,&n);

printf("Selected points:\n");
int i;
for (i=0;i<2*n;i=i+2)
  {
  printf("(%lf,%lf)\n",points[i],points[i+1]);
  }
return 0;
}

```