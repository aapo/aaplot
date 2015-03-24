/*
Linked list.
Node contains
-window
-camera[]
-target[]
-width,height
-scale (x,y,z)
-are we moving the contents
-are we rotating the contents
-zoom-factor (move_divider)
-title
-backgound-color
-rotating matrix (see aaplot_helper.c)
-tables / functions
-mode
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

#define ROTATE_MODE 100001
#define MOVING_MODE 100002

typedef struct ns3 {
      float camera[3],target[3]; /* Location of the camera and its target*/
      int width;    /*width of the window*/
      int height;    /*heigth of the window*/
      double scale[3];   /*x_scale, y_scale, z_scale */

      int moving,startx, starty; /*first is state-boolean, anothers are coordinates*/
      int rotating, rstartx,rstarty;
      float move_divider;
      int id;
	   char *title;
      double background_color[3];
      float rotation_matrix[16];
      function_node *functions; /*all functions which that window owns*/
      table_node *tables;  /*all tables which that window owns*/
      point *user_clicked; /*one point-list if user want clicks points from the screen*/
      int mode;
      double mouse_x,mouse_y; /*coordinates of mouse pointer*/
      int menuID; /*contains handle to the this window's menu */

      /*boundaries*/
      double lower_bounds[3];
      double upper_bounds[3];

      double x_grid;
      double y_grid;
      double z_grid;

      int coordplane[3];
      struct ns3 *next;
} window;


/*fix,make extern*/
window *windows = NULL;

/*Add node to the first of the list.
*/
void add_window(int width, int height, char *title) {
   window *n = malloc(sizeof(window));
   if (n == NULL)
     {
     //printf("memory allocation failed\n");
     return ;
     }


   n->next = windows;
   windows = n;
   n->camera[0]=default_camera[0];
   n->camera[1]=default_camera[1];
   n->camera[2]=default_camera[2];
   n->target[0]=default_target[0];
   n->target[1]=default_target[1];
   n->target[2]=default_target[2];

   n->background_color[0] = default_background_color[0];
   n->background_color[1] = default_background_color[1];
   n->background_color[2] = default_background_color[2];

   n->lower_bounds[0]=default_lower_bounds[0];
   n->lower_bounds[1]=default_lower_bounds[1];
   n->lower_bounds[2]=default_lower_bounds[2];

   n->upper_bounds[0]=default_upper_bounds[0];
   n->upper_bounds[1]=default_upper_bounds[1];
   n->upper_bounds[2]=default_upper_bounds[2];


   n->x_grid=default_x_grid;
   n->y_grid=default_y_grid;
   n->z_grid=default_z_grid;

   n->coordplane[0] = default_coordplane[0];
   n->coordplane[1] = default_coordplane[1];
   n->coordplane[2] = default_coordplane[2];

   n->scale[0] = 1;
   n->scale[1] = 1;
   n->scale[2] = 1;
   n->width = width;
   n->height = height;
   n->moving = 0;
   n->title = title;
   n->functions = NULL;
   n->tables = NULL;
   n->user_clicked = NULL;
   n->mode=MOVING_MODE;
   init_rotation_matrix(n->rotation_matrix);
}
