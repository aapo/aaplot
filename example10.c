
/*
taustan varin vaihto
default_background_color[0]=1.0;
default_background_color[1]=0.0;
default_background_color[2]=0.0;
*/
#include "aaplot.h"

double f(double x) {
return x*x;
}

int main(void)
{


double p[1],p2[1],p3[2],p4[1],p5[1];
addRFunction(0        /* window number        */
            ,&f       /* function             */
            ,3.0      /* size of points       */
            ,0.1     /* stepping of x        */
            ,"x * x");  /* title of function    */
          
/*oletus-rajat loytyvat tiedostosta aaplot_defaults.c
mitaan ei piirreta rajojen ulkopuolelle
(poikkeuksena akselien suunnan nayttavat nuolet) */
lower_z_limit = -10.0;
upper_z_limit = 10.0; 

lower_y_limit = -10.0;
upper_y_limit = 10.0;

lower_x_limit = -4.0;
upper_x_limit = 4.0;

drawAll(); /*suoritus pysahtyy tahan kunnes kaikki graafiset ikkunat on suljettu*/
printf("valmista tuli\n");
return 0;
}


