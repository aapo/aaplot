
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define AAPLOT_SCREENSHOT
#define AAPLOT_ICON

void refresh ();
void drawAll();

void changeEntityColor(int id, float red, float green, float blue);
void changeEntityPlotSize(int id, int size);
void changeEntityXStepping(int id, double x_step);
void changeEntityZStepping(int id, double z_step); 

void setWindowAttribute(int win, char* attrib, double x);
double *getClickedPointsFromWindow(int win, int *n);


int addRFunction(int win,double (*func_ptr)(double), double step, char *s);
int addRFunctionWithP(int win,double (*func_ptr)(double,double*),double *para, double step, char *s);
int addR2Function(int win,double (*func_ptr)(double,double), double x_step, double z_step, char *s);
int addR2FunctionWithP(int win,double (*func_ptr)(double,double,double*),double *para, double x_step, double z_step, char *s);



int addRCurve(int win,void (*curve_ptr)(double,double*,double*,double*), double step, double lower, double upper, char *s);
int addRCurveWithP(int win,void (*curve_ptr)(double,double*,double*,double*,double*),double *para, double step, double lower, double upper, char *s);
int addTableDataFile(int win,char *file, char *s);
int addTableDataArrays(int win,int count,double x[],double y[], char *s);

extern double default_background_color[3];
extern int default_coordplane[3];

extern int default_window_width;
extern int default_window_height;

extern double width_of_the_axis;

extern double default_lower_x_limit;
extern double default_upper_x_limit;

extern double default_lower_y_limit;
extern double default_upper_y_limit;

extern double default_lower_z_limit;
extern double default_upper_z_limit;

extern double default_size;

extern char *default_name;
//double default_step = 0.0001;

extern float default_camera[3];
extern float default_target[3];


extern double default_y_grid;  /* density of grid. 0=no grid*/
extern double default_x_grid;
extern double default_z_grid;






