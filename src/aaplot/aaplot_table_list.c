
/*
Linked list.
Node contains
-pointlist (x,y,z)
-size of points
-color
-title

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
        point *points;
        double size;
        float red;
        float green;
        float blue;
        char *name;
        int hidden;
        int direction[3];
        int id;
        struct ns5 *next;
} table_node;


/*Add node to the first of the list.
Returns id-number of the new node. Or -1 in the error situation.
*/
int add_table(table_node **tables, point *pl, char* s,float red, float green, float blue) {
    table_node *n = malloc(sizeof(table_node));
    if (n == NULL)
      {
      printf("memory allocation failed\n");
      return -1;
      }

    n->next = *tables;
    *tables = n;

    n->points=pl;
    n->size = default_size;
    n->name = s;
    n->red = red;
    n->green = green;
    n->blue = blue;
    n->hidden = 0;

    n->direction[0] = 0;
    n->direction[1] = 1;
    n->direction[2] = 2;

    n->id=entity_id_counter;
    entity_id_counter++;
    return n->id;
}
