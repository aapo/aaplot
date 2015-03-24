
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

typedef struct ns5 {
        point *pisteet;      
        double size;
        float red;
        float green;
        float blue;
        int id;
        char *name;
        struct ns5 *next;
} table;


/*Add node to the first of the list.
Returns id-number of the new node. Or -1 in the error situation.
*/
void add_table(table **taulukot, point *pl, double size, char* s,float red, float green, float blue) {

    table *n = (table *)malloc(sizeof(table));
    if (n == NULL)
      { 
      printf("muistin varaus epaonnistui\n");
      return ;
      }

      n->next = *taulukot;
      *taulukot = n;
      
      n->pisteet=pl;
    

    n->size = size;
    
    n->name = s;
    n->red = red;
    n->green = green;
    n->blue = blue;
/*    n->id=id_counter;
    id_counter++;
    return n->id;*/
}
