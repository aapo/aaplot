#define AAPLOT_SCREENSHOT

/*background color: 1,1,1=white. 0,0,0=black*/
double default_background_color[3] = {1.0,1.0,1.0} ;

int default_window_width = 500;
int default_window_height = 500;

double width_of_the_axis = 2.0;

double lower_x_limit = -10.0;
double upper_x_limit = 10.0;

double lower_y_limit = -5.0;
double upper_y_limit = 5.0;

double lower_z_limit = -3.0;
double upper_z_limit = 3.0;


char *default_name ="funktio";
double default_size = 1.0;
double default_step = 0.0001;
double default_red = 1;
double default_green = 0;
double default_blue = 1;




/*what is density of grid. 0=no grid*/
double y_grid=1;

double x_grid=1;

/*not in use: double z_grid=0;*/

#define axisArrows
