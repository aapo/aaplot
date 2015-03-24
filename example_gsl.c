/*
This example show how use aaplot with gsl
see: http://www.gnu.org/software/gsl/

First we make gsl_matrix. In this case we just load it from file.
Then we divide matrix to two arrays and continue like example4.
*/
#include "aaplot.c"
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_linalg.h>

/* Reads a table from a file and store it to gsl_matrix. */
gsl_matrix *loadMatrix(char *file_name)
{
gsl_matrix *matrix;
  FILE *fp;
  int i,j,m,n;
  float inp;
  fp=fopen(file_name,"r");
  if (!fp) 
    {
    fprintf(stderr,"Cannot open file %s\n",file_name);
    exit(1);
    }
  if (fscanf(fp,"%d %d",&m,&n)!=2)
     printf("Bad matrix file");
  matrix=gsl_matrix_alloc(m,n);
  for (i=0;i<m;i++)
    {
    for (j=0;j<n;j++) 
      {
      fscanf(fp," %f",&inp);
      gsl_matrix_set(matrix,i,j,(double)inp);
      }
    fscanf(fp,"\n");
    }
  fclose(fp);
  return matrix;
}

int matrix_to_arrays(gsl_matrix *a,double *x,double *y) {
int i;
  for (i=0;i<a->size1;i++)
   {
   x[i]=gsl_matrix_get(a,i,0);
   y[i]=gsl_matrix_get(a,i,1);
   }
return i;
}


int main(void)    {
lower_z_limit = -6.0;
upper_z_limit = 6.0;

lower_y_limit = -6.0;
upper_y_limit = 6.0;

lower_x_limit = -6.0;
upper_x_limit = 6.0;

y_ruudukko=0;
x_ruudukko=0;
gsl_matrix *matrix = loadMatrix("aalto.dat"); 

#define MAXPOINTS 1000
double x[MAXPOINTS];
double y[MAXPOINTS];

int number_of_points=matrix_to_arrays(matrix,&x[0],&y[0]);
addTableDataArrays(0,number_of_points,x,y,2, "gsl_matrix");

drawAll();
return 0;
}


