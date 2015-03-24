
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
Returns id-number of the new node. Or -1 in the error situation.
*/
void add_point(point **jono, double x,double y,double z) {
    point *n = (point *)malloc(sizeof(point));
    if (n == NULL)
      { 
      printf("muistin varaus epaonnistui\n");
      return ;
      }
    n->x=x;
    n->y=y;
    n->z=z;
    
    n->next = *jono;
    *jono = n;

}

point *teeJono(int count,double x[],double y[]) {
point *pl=NULL;
int i;
for (i=0;i<count;i++)
   {
   add_point(&pl,x[i],y[i],1);
   }
return pl;
}
/*
tiedoston nimi, mitka akselit mihinkin ja mika on viimeisen arvo jos ei
kaytossa.
*/
point *loadFile(char *file_name)
{

  FILE *fp;
  int i,m,n;
  float eka,toka;
  point *pl=NULL;

  fp=fopen(file_name,"r");
  if (!fp) 
    {
    fprintf(stderr,"Cannot open file %s\n",file_name);
    exit(1);
    }
  if (fscanf(fp,"%d %d",&m,&n)!=2)
     printf("Bad matrix file");

/*fix, arvaa, etta on kaksi ulottoinen, 
toteuta myos kolmiulotteinen*/
  for (i=0;i<m;i++)
    {
    fscanf(fp," %f",&eka);
    fscanf(fp," %f",&toka);
    add_point(&pl,eka,toka,0);
    fscanf(fp,"\n");
    }
  fclose(fp);
  return pl;
}
