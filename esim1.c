/*piirtaa R2->R funktion, joka on maaritelty paloittain
(suora avaruudessa) 
iso askellus.  */
#include "aaplot.c"

/*paloittain maaritelty funktio*/
double f2(double x,double z) {
double eps=0.01; /*ei verrata doubleja suoraan toisiinsa */
if (fabs(x-z)<eps) 
   return x;
else 
   return upper_y_limit+1; /*tama tarkoittaa etta ei maaritelty*/
}


int main(void)    {

addR2Function(0,                     /* window number        */
              &f2,                   /* function             */
              0.1,                   /* stepping of x        */
              0.1,                   /* stepping of z        */
              "abcdefghijklmnopqrstuvwxyz"   /* title of function    */
              );                /* colors in RGB [0,1]  */


addR2Function(0,                     /* window number        */
              &f2,                   /* function             */
              0.1,                   /* stepping of x        */
              0.1,                   /* stepping of z        */
              "ABCDEFGHIJKLMNOPQRSTUVWXYZ"  /* title of function    */
              );                /* colors in RGB [0,1]  */

addTableDataFile(0,"aalto.dat" , "aalto26");

drawAll();
return 0;
}


