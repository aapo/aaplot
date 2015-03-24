/*One function and one table.
Changing attributes of them.
*/
#include "aaplot.c"

double f(double x) {
return sin(x);
}


int main() { 
int f_id = addRFunction(0,&f,0.01,"sin x");

/*entity_id, red,green,blue*/
changeEntityColor(f_id,0,1,0);

/*entity_id, plot_size*/
changeEntityPlotSize(f_id,4.54);


int t_id= addTableDataFile(0,"aalto2.dat", "aalto100");
changeEntityColor(t_id,1,0,1);
changeEntityPlotSize(t_id,6.75);


drawAll();
return 0;
}
