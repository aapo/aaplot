/*One function and one table.
Changing attributes of them.
*/
#include "aaplot.h"

double f(double x) {
return sin(x);
}


int main() { 
int f_id = addRFunction(0,&f,0.001,"sin x");

/*entity_id, red,green,blue: double between [0,1] */
changeEntityColor(f_id,0,1,0);

/*entity_id, plot_size*/
changeEntityPlotSize(f_id,4.54);

/*entity_id, stepping0: if function is f(z)=x then step0 = z */
changeEntityStepping0(f_id, 0.1);

/*entity_id, stepping1: if function is f(z)=x then there are no step1 */
changeEntityStepping1(f_id, 0.1); /*do nothing, because of function dimension*/


int t_id= addTableDataFile(0,"aalto2.dat", "aalto100");
changeEntityColor(t_id,1,0,1);
changeEntityPlotSize(t_id,6.75);
changeEntityTitle(t_id, "new Title");

drawAll();
return 0;
}
