/*
Linked list.
Node contains
-window
-camera[]
-target[]
-width,height
-are we moving the contents
-are we rotating the contents
-zoom-factor (move_divider)
-title
-backgound-color
-rotating matrix (see aaplot_helper.c)
-id_number

New nodes goes to first of the list.

Time
Adding O(1)
Removing O(n)
Printing O(n)
Where n is number of nodes.
*/
#include <stdio.h>   /* for printf */
#include <stdlib.h>  /* for malloc */


typedef struct ns3 {
      float camera[3],target[3]; /* Location of the camera and its target*/
      int width;    /*width of the window*/
      int height;    /*heigth of the window*/

      int moving,startx, starty; /*first is state-boolean, anothers are coordinates*/
      int rotating, rstartx,rstarty;
      float move_divider;
      int id;
	   char *title;
      double background_color[3];
      float rotation_matrix[16];
      node *functions; /*all functions which that window owns*/
      table *tables;  /*all tables which that window owns*/
      struct ns3 *next;
} window;


/*fix,make extern*/
window *windows = NULL; 

/*Add node to the first of the list.
*/
void add_window(int width, int height, char *title) {
    window *n = (window *)malloc(sizeof(window));
    if (n == NULL)
      {
      printf("memory allocation failed\n");
      return ;
      }

   float  camera[3],target[3];
   target[0] = 0;
   target[1] = 4.0;
   target[2] = 0;
   camera[0] = 0;
   camera[1] = 4.0;
   camera[2] = 10;


    n->next = windows;
    windows = n;
    n->camera[0]=camera[0];
    n->camera[1]=camera[1];
    n->camera[2]=camera[2];
    n->target[0]=target[0];
    n->target[1]=target[1];
    n->target[2]=target[2];
    
    n->background_color[0] = default_background_color[0];
    n->background_color[1] = default_background_color[1];
    n->background_color[2] = default_background_color[2];

    n->width = width;
    n->height = height;
    n->moving = 0;
    n->title = title;
    n->functions = NULL;
    n->tables = NULL;
    init_rotation_matrix(n->rotation_matrix);   
}


#ifdef not_tested
void list_remove(int id) {
   node *n = funktiot;
   node *edellinen = funktiot;
   if (n == NULL)
      {
      /*printf("list is empty\n");*/
      return;
      }

   /*removing the first is special case   */
   if (n->id==id)
      {
      funktiot=n->next;
      return;
      }

   while (n != NULL)
      {
      if (n->id==id)
         {
         edellinen->next=n->next;
         return;
         }
      edellinen=n;
      n = n->next;
      }
}

void list_removeB(double (*f)(double)) {
   node *n = funktiot;
   node *edellinen = funktiot;
   if (n == NULL)
      {
      /*printf("list is empty\n");*/
      return;
      }

   /*removing the first is special case   */
   if (n->function==f)
      {
      funktiot=n->next;
      return;
      }

   while (n != NULL)
      {
   if (n->function==f)
         {
         edellinen->next=n->next;
         return;
         }
      edellinen=n;
      n = n->next;
      }
}
#endif
