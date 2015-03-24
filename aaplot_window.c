  /*
Linked list.
Node contains
-window
-camera[]
-target[]

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
      float  camera[3],target[3]; /* Location of the camera and its target*/
      int width;    /*width of the window*/
      int height;    /*heigth of the window*/

      int moving,startx, starty; /*first is state-boolean, anothers are coordinates*/
      int rotating, rstartx,rstarty;
      float move_divider;
       
	   char *title;
      double background_color[3];
      float rotation_matrix[16];
      int id;
      node *funktiot; /*kaikki tahan ikkunaan liittyvat funktiot*/
      table *taulukot;  /*kaikki tahan ikkunaan liittyvat taulukkodatat*/
      struct ns3 *next;
} window;


/*fix, tasta extern.*/
window *windows = NULL; 

/*Add node to the first of the list.
*/
void list3_add(float camera[3], float target[3], 
            int width, int height,            
            char *title) {
    window *n = (window *)malloc(sizeof(window));
    if (n == NULL)
      {
      printf("muistin varaus epaonnistui\n");
      return ;
      }

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
    n->funktiot = NULL;
    n->taulukot = NULL;
    init_rotation_matrix(n->rotation_matrix);   
}


#ifdef eiviel
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
#endif

#ifdef eikaytossa
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
