
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef _MSC_VER
#define OPENGLUT_STATIC
#endif

#if __STRICT_ANSI__
#define M_PI 3.14159265358979323846264338327
#endif

void refresh ();
void drawAll();

void toggleHidden(int id);

/*
direction   R2->R        3dT    R->R      2dT
 0          f(x,y)=z     xyz   f(x)=y      XY
 1          f(x,z)=y     xzy   f(x)=z      XZ
 2          f(y,x)=z     yxz   f(y)=x      YX
 3          f(y,z)=x     yzx   f(y)=z      YZ
 4          f(z,x)=y     zxy   f(z)=x      ZX
 5          f(z,y)=x     zyx   f(z)=y      ZY
*/
void changeDirection(int id, int d);
void changeEntityColor(int id, float red, float green, float blue);
void changeEntityPlotSize(int id, int size);
void changeEntityStepping0(int id, double x_step);
void changeEntityStepping1(int id, double z_step);
void changeEntityTitle(int id, char *title);

void setWindowAttribute(int win, char* attrib, double x);
double *getClickedPointsFromWindow(int win, int *n);


int addRFunction(int win,double (*func_ptr)(double), double step, char *s);
int addRFunctionWithP(int win,double (*func_ptr)(double,double*),double *para, double step, char *s);
int addR2Function(int win,double (*func_ptr)(double,double), double x_step, double z_step, char *s);
int addR2FunctionWithP(int win,double (*func_ptr)(double,double,double*),double *para, double x_step, double z_step, char *s);



int addRCurve(int win,void (*curve_ptr)(double,double*,double*,double*), double step, double lower, double upper, char *s);
int addRCurveWithP(int win,void (*curve_ptr)(double,double*,double*,double*,double*),double *para, double step, double lower, double upper, char *s);

int addR2Curve(int win,void (*curve_ptr)(double,double,double*,double*,double*), double step, double step_1,double lowerA, double upperA, double lowerB, double upperB, char *s);

int addR2CurveWithP(int win,void (*curve_ptr)(double,double,double*,double*,double*,double*),double *para, double step, double step_1,double lowerA, double upperA, double lowerB, double upperB, char *s);

int addTableDataFile(int win,char *file, char *s);
int addTableDataArrays(int win,int count,double x[],double y[], char *s);
int addTableDataArrays3d(int win,int count,double x[],double y[], double z[], char *s);

extern double default_background_color[3];
extern int default_coordplane[3];

extern int default_window_width;
extern int default_window_height;

extern double width_of_the_axis;

extern double default_lower_bounds[3];
extern double default_upper_bounds[3];


extern double default_size;

extern char *default_name;

extern float default_camera[3];
extern float default_target[3];


extern double default_y_grid;  /* density of grid. 0=no grid*/
extern double default_x_grid;
extern double default_z_grid;

extern double default_2dtable_thirdvalue;

