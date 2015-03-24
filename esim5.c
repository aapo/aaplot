/*piirtaa kolmeen ikkunaan funktioita*/
#include "aaplot.c"

double g(double x) {
return x*x;
}

double g2(double x) {
return 2*x;
}

double f(double x) {
return sin(x);
}

double f2(double x) {
return cos(x);
}


int main(void) { 
addRFunction(0,&f, CONTINUOS,1.0,0.01,"sin x",1,0,1);
addRFunction(1,&g, CONTINUOS,1.0,0.01,"x*x",0,1,1);

addRFunction(2,&f2, CONTINUOS,1.0,0.01,"cos x",1,0,1);
addRFunction(2,&g2, CONTINUOS,1.0,0.01,"x*x",0,1,1);

lower_z_limit = 0.0;
upper_z_limit = 0.0; 

lower_y_limit = -4.0;
upper_y_limit = 4.0;

lower_x_limit = -4.0;
upper_x_limit = 4.0;

drawAll();
return 0;
}
