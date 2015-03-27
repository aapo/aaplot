
/*
Linked list.
Node contains
-one point (x,y,z)

New nodes goes to first of the list.

Time
Adding O(1)
Removing O(n)
Printing O(n)

Where n is number of nodes.
*/
#include <stdio.h>   /* for printf */
#include <stdlib.h>  /* for malloc */

typedef struct ns4 {
        double x;
        double y;
        double z;
        struct ns4 *next;
} point;



/*Add node to the first of the list.
*/
void add_point(point **list, double x,double y,double z) {
    point *n = malloc(sizeof(point));
    if (n == NULL)
      {
      //printf("memory allocation failed\n");
      return ;
      }
    n->x=x;
    n->y=y;
    n->z=z;

    n->next = *list;
    *list = n;
}

point *makeList(int count,double x[],double y[]) {
point *pl=NULL;
int i;
for (i=0;i<count;i++)
   {
   add_point(&pl,x[i],y[i],default_2dtable_thirdvalue);
   }
return pl;
}

point *makeList3d(int count,double x[],double y[],double z[]) {
point *pl=NULL;
int i;
for (i=0;i<count;i++)
   {
   add_point(&pl,x[i],y[i],z[i]);
   }
return pl;
}

point *loadFile(char *file_name)
{

  FILE *fp;
  int i,m,n;
  double first,second,third;
  point *pl=NULL;

  fp=fopen(file_name,"r");
  if (!fp)
    {
    fprintf(stderr,"Cannot open file %s\n",file_name);
    exit(1);
    }
  if (fscanf(fp,"%d %d",&m,&n)!=2)
     fprintf(stderr,"Bad matrix file (a)\n");

  for (i=0;i<m;i++)
    {
    if (fscanf(fp," %lf",&first) != 1)
        fprintf(stderr,"Bad matrix file (b)\n");
    if (fscanf(fp," %lf",&second) != 1)
        fprintf(stderr,"Bad matrix file (c)\n");

    if (n==3)
      {
      if(fscanf(fp," %lf",&third) != 1)
        fprintf(stderr,"Bad matrix file (d)\n");
      }
    else
      third=default_2dtable_thirdvalue;
    add_point(&pl,first,second,third);
    if (fscanf(fp,"\n") != 0)
        fprintf(stderr,"Bad matrix file (e)\n");
    }
  fclose(fp);
  return pl;
}
