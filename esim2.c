/*piirtaa kahden eri tiedoston pisteet
aaltomaljakko 26:lla / 100:lla pisteella

lisaksi piirtaa lennossa tehtyjen taulukkojen arvot
tulkiten ne koordinaateiksi (x,y,1) */

#include "aaplot.c"


int main(void)    {
/*ikkuna,tiedosto,pisteen koko, otsikko, RGB */
addTableDataFile(0,"aalto.dat" ,3, "aalto26",0,0,1); 
addTableDataFile(1,"aalto2.dat",2, "aalto100",1,1,1);


#define number_of_points 10
double x[number_of_points];
double y[number_of_points];

int i=0;
for (i=0;i<number_of_points;i++)
  {
  x[i]=i*cos(i);
  y[i]=i*sin(i);
  }
/*ikkuna,taulukkojen koko, x-koordinaatit, y-koordinaatit,pisteen koko, otsikko, RGB */
addTableDataArrays(0,number_of_points,x,y,2, "testiDataa",0,1,0);

drawAll();
return 0;
}

