
#include "aaplot.h"

/*there are globals, that we need before including other files*/
/*background color: 1,1,1=white. 0,0,0=black*/
double default_background_color[3] = {1.0,1.0,1.0};
int default_coordplane[3] ={1,0,0}; /*XY, YZ, ZX*/

int default_window_width = 500;
int default_window_height = 500;

double width_of_the_axis = 2.0;

double default_lower_x_limit = -10.0;
double default_upper_x_limit = 10.0;

double default_lower_y_limit = -5.0;
double default_upper_y_limit = 5.0;

double default_lower_z_limit = -3.0;
double default_upper_z_limit = 3.0;

double default_size = 2.0;

char *default_name ="function";
//double default_step = 0.0001;

float  default_camera[3] = {1, 4.0  , 10};
float  default_target[3] = {1, 4.0  , 0};


double default_y_grid=1;  /* density of grid. 0=no grid*/
double default_x_grid=2;
double default_z_grid=0.5;

#define axisArrows


#ifdef AAPLOT_SCREENSHOT
#include <png.h>
#endif

#include "openglut.h"
#include "aaplot_helper.c"
#include "aaplot_func_list.c"
#include "aaplot_point_list.c"
#include "aaplot_table_list.c"
#include "aaplot_screenshot.c"
#include "aaplot_window.c"
#include "aaplot_inputbox.c"

#if !defined(GLUT_WHEEL_UP)
#  define GLUT_WHEEL_UP   3
#  define GLUT_WHEEL_DOWN 4
#endif

/*Think*/
/* Not even todo-list, just think-list.

should every window has own 
 -width_of_the_axis
 -color of axis


*/


/*
Some links:
http://www.opengl.org/documentation/specs/glut/spec3/node1.html
*/

/*GLOBALS*/
int is_initialized = 0;
extern window *windows;
int numbers_of_windows=0;


/*Refresh all windows. (eg. glutPostRedisplay() in every)
*/
void refresh ()
 {
 window *w = windows;
 while (w != NULL)
   {
   glutSetWindow(w->id);
   glutPostRedisplay();
   w=w->next;
   }
 }


window *getCurrentWindow(){
 int win = glutGetWindow();
   window *w = windows;
   while (w != NULL)
        {
        if (w->id==win)
          {
          break;
          }
        w=w->next;
        }
return w;
}

window *get_window_by_int(int win)
   {
   window *w = windows;
   int i;
   for (i=0;i<numbers_of_windows-win-1;i++)
      {
      w=w->next;
      }
   return w;
   }


/*
Check in every windows every FUNCTIONS and looking for given function id.
Returns NULL if there are no such a id_number.
*/

function_node *getFunctionById(int f_id) {
 window *w = windows;
 while (w != NULL)
   {
   function_node *n = w->functions;
   while (n != NULL)
      {
      if (n->id == f_id)
         {
         return n;
         }
      n = n->next;
      }
   w=w->next;
   }
 return NULL;
 }

/*
Check in every windows every TABLE and looking for given function id.
Returns NULL if there are no such a id_number.
*/
table_node *getTableById(int t_id) {
 window *w = windows;
 while (w != NULL)
   {
   table_node *n = w->tables;
   while (n != NULL)
      {
      if (n->id == t_id)
         {
         return n;
         }
      n = n->next;
      }
   w=w->next;
   }
 return NULL;
 }


/*Window builds (only) its own content*/
void buildModel( window *w )
   {
   int amount=0;   /*we use this to printing legend*/
   glClearColor(w->background_color[0],
                w->background_color[1],
                w->background_color[2],
                                    0); /*this last is alpha channel*/

   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
   glPushMatrix();
   glScaled(w->scale[0],w->scale[1],w->scale[2]);

   /*Axis*/
   glLineWidth(width_of_the_axis);
   glBegin(GL_LINES);
   /* X-axis with red*/
   glColor3f(1,0,0);
   glVertex3f(w->lower_x_limit,0,0);
   glVertex3f(w->upper_x_limit,0,0);

   /* Y-axis with green*/
   glColor3f(0,1,0);
   glVertex3f(0,w->lower_y_limit,0);
   glVertex3f(0,w->upper_y_limit,0);

   /* Z-axis with blue*/
   glColor3f(0,0,1);
   glVertex3f(0,0,w->lower_z_limit);
   glVertex3f(0,0,w->upper_z_limit);
   glEnd();
 

/*  Gridding */
///////////////
/*XY-plane */
if (w->coordplane[0])
   {
   glPushMatrix();

   grid_helper(w->y_grid,w->upper_x_limit,w->lower_x_limit,w->upper_y_limit,w->lower_y_limit);

   glTranslatef(w->upper_x_limit + w->lower_x_limit,0,0);
   glRotatef(90,0,0, 1.0);

   grid_helper(w->x_grid,w->upper_y_limit,w->lower_y_limit,w->upper_x_limit,w->lower_x_limit);
   glPopMatrix();
   }


/*YZ-plane */
if (w->coordplane[1])
   {
   glPushMatrix();
   glRotatef(270,0,1,0);

   grid_helper(w->y_grid,w->upper_z_limit,w->lower_z_limit,w->upper_y_limit,w->lower_y_limit);

   glTranslatef(w->upper_z_limit + w->lower_z_limit,0,0);
   glRotatef(90,0,0, 1.0);

   grid_helper(w->z_grid,w->upper_y_limit,w->lower_y_limit,w->upper_z_limit,w->lower_z_limit);
   glPopMatrix();
   }

/*XZ-plane */
if (w->coordplane[2])
   {
   glPushMatrix();
   glRotatef(90,1,0,0);

   grid_helper(w->z_grid,w->upper_x_limit,w->lower_x_limit,w->upper_z_limit,w->lower_z_limit);

   glTranslatef(w->upper_x_limit + w->lower_x_limit,0,0);
   glRotatef(90,0,0, 1.0);

   grid_helper(w->x_grid,w->upper_z_limit,w->lower_z_limit,w->upper_x_limit,w->lower_x_limit);
   glPopMatrix();
   }


/*y-axis parallel scale-numbers */
   {
   double x;
   glLineWidth(1.0);
   glColor3f(0,0,0);

   for (x=0.0;x<=w->upper_x_limit;x=x+w->y_grid)
      {
      glPushMatrix();
      glTranslatef(x-0.05,0.05,0.0);
      glScaled(0.002,0.002,0.002);
      char message[10];
      sprintf(message,"%2.2lf",x);
      glutStrokeString(NULL,message);
      glPopMatrix();
      }
   for (x=0.0;x>=w->lower_x_limit;x=x-w->y_grid)
      {
      glPushMatrix();
      glTranslatef(x-0.05,0.05,0.0);
      glScaled(0.002,0.002,0.002);
      char message[10];
      sprintf(message,"%2.2lf",x);
      glutStrokeString(NULL,message);
      glPopMatrix();
      }
   }

/*x-axis parallel scale-numbers */
   {
   double y;
   glLineWidth(1.0);
   glColor3f(0,0,0);

   for (y=0.0;y<=w->upper_y_limit;y=y+w->x_grid)
      {
      glPushMatrix();
      glTranslatef(0.0,y-0.05,0.0);
      glScaled(0.002,0.002,0.002);
      char message[10];
      sprintf(message,"%2.2lf",y);
      glutStrokeString(NULL,message);
      glPopMatrix();
      }
   for (y=0.0;y>=w->lower_y_limit;y=y-w->x_grid)
      {
      glPushMatrix();
      glTranslatef(0.0,y-0.05,0.0);
      glScaled(0.002,0.002,0.002);
      char message[10];
      sprintf(message,"%2.2lf",y);
      glutStrokeString(NULL,message);
      glPopMatrix();
      }
   }


  char coordinates[200];
  sprintf(coordinates,"(%lf,%lf)",w->mouse_x,w->mouse_y);
draw_text(1, 0,coordinates,1,0,0);


#ifdef axisArrows
   glPushMatrix();
   glColor3f(1.0,0.0,0.0);
   glTranslatef(1.0,0.0,0.0);
   glRotatef(90,0.0,1.0,0.0);
   glutSolidCone(0.05,0.1,10,10);
   glPopMatrix();
   glPushMatrix();
   glColor3f(0.0,1.0,0.0);
   glTranslatef(0.0,1.0,0.0);
   glRotatef(-90,1.0,0.0,0.0);
   glutSolidCone(0.05,0.1,10,10);
   glPopMatrix();
   glPushMatrix();
   glColor3f(0.0,0.0,1.0);
   glTranslatef(0.0,0.0,1.0);
   glutSolidCone(0.05,0.1,10,10);
   glPopMatrix();
#endif

/*Axis+grids+etc ready////////////////*/
/*////////////////////////////////////*/


/*******  Functions Start************/
/*//////////////////////////////////*/
{
function_node *n = w->functions;
while (n != NULL)
   {
   double j;
   double y;
   double i;
   int parameters=0;    /*this will be 1, if WithParameters-version*/
   
   if (n->hidden) /* skip this function totally*/
      {
      n = n->next;
      continue; 
      }

   glPointSize(n->size);
   glColor3f(n->red,n->green,n->blue);


if (n->type>10)
   {
   parameters=1;
   }


/******** R->R  ************/
if (n->type%10==1)
   {
   glBegin(GL_POINTS);
   for (j=w->lower_x_limit;j<w->upper_x_limit;j=j+n->x_step)
      {
      y=     parameters==0 ? n->function(j)   :  n->function_p(j,n->parameters);
      if (y>=w->lower_y_limit && y<=w->upper_y_limit)
         {
         glVertex3f(j,y,0);
         }
      }
   glEnd();
   }

/******** R^2->R  **********/
if (n->type%10==2)
   {
   glBegin(GL_POINTS);
   for (i=w->lower_z_limit;i<w->upper_z_limit;i=i+n->z_step)
      {
      for (j=w->lower_x_limit;j<w->upper_x_limit;j=j+n->x_step)
         {
         y=   parameters==0 ? n->function2(j,i)  :  n->function2_p(j,i,n->parameters);
         if (y>=w->lower_y_limit && y<=w->upper_y_limit)
            glVertex3f(j,y,i);
         }
      }
   glEnd();
   }

/***curves R -> R^3  *******/
if (n->type%10==3)
   {
   double alfa;
   double x,y,z;
   glBegin(GL_POINTS);
   for (alfa=n->lower_alfa;alfa < n->upper_alfa;alfa=alfa+n->x_step)
      {
      parameters==0 ?  n->curve(alfa,&x,&y,&z)  :  n->curve_p(alfa,&x,&y,&z,n->parameters);
      if (x>=w->lower_x_limit && x<=w->upper_x_limit &&
          y>=w->lower_y_limit && y<=w->upper_y_limit &&
          z>=w->lower_z_limit && z<=w->upper_z_limit)
         glVertex3f(x,y,z);
      }
   glEnd();
   }

amount++;
draw_text(1, amount,n->name,n->red,n->green,n->blue);
n = n->next;
}
}
/*******  Functions Ready************/
/*//////////////////////////////////*/


/*******  Arrays Start************/
/*///////////////////////////////*/
{
table_node *t = w->tables;
while (t != NULL)
   {
   point *p = t->points;
   glPointSize(t->size);
   glColor3f(t->red,t->green,t->blue);
   glBegin(GL_POINTS);
   while (p != NULL)
      {
      double x=p->x;
      double y=p->y;
      double z=p->z;
      if (x>w->lower_x_limit && x<w->upper_x_limit &&
          y>w->lower_y_limit && y<w->upper_y_limit &&
          z>w->lower_z_limit && z<w->upper_z_limit )
         glVertex3f(x,y,z);
      p=p->next;
      }
   glEnd();

   amount++;
   draw_text(1, amount,t->name,t->red,t->green,t->blue); 
   t = t->next;
   }
}
/*******  Arrays Ready************/
/*///////////////////////////////*/

/*******  User-Clicked start************/
/*///////////////////////////////*/
{ 
point *p = w->user_clicked;
if (p != NULL)
   {
   glPointSize(4.0);
   glColor3f(1,0,0);
   glBegin(GL_POINTS);
   while (p != NULL)
      {
      double x=p->x;
      double y=p->y;
      double z=p->z;
      if (x>w->lower_x_limit && x<w->upper_x_limit &&
          y>w->lower_y_limit && y<w->upper_y_limit &&
          z>w->lower_z_limit && z<w->upper_z_limit )
         glVertex3f(x,y,z);
      p=p->next;
      }
   glEnd();
   
   amount++;
   draw_text(1, amount,"User clicked",1,0,0);   
   }
}
/*******   User-Clicked Ready************/
/*///////////////////////////////*/


/*******  Arrays Ready************/
/*///////////////////////////////*/
  glPopMatrix();
/*video casting*/
/*  PNGScreenShot(w->width, w->height); */
}



/*This is called when some window needs repaintting (only that window is repainted)*/
void display()
   {
   int win = glutGetWindow();
   GLint viewport[4];
   window *w = windows;
   glGetIntegerv( GL_VIEWPORT, viewport );
   glCullFace(GL_BACK);
   glEnable( GL_DEPTH_TEST );

   while (w != NULL)
      {
      if (w->id == win)
         {
         glLoadIdentity();
         look_at(w->camera[0], w->camera[1], w->camera[2],
                 w->target[0], w->target[1], w->target[2] );

         glMultMatrixf(w->rotation_matrix);    /*rotating */
         buildModel(w);
         break;
         }
      w=w->next;
      }
   glutSwapBuffers();
   }


/* //This is not yet ready. Zooming, point clicking, reshaping etc. works only with fov=90.
void goOrtho() {
window *w = windows;
 w->camera[2]=6300;

   glMatrixMode(GL_PROJECTION);
         glLoadIdentity();

         perspective(0.1,4/3,0.0001,20000.0);

         glMatrixMode (GL_MODELVIEW);
refresh();
}
*/

/*This is called when size of some window is changed (only that window is in processing)*/
void reshape(int width, int h)
   {
   int win = glutGetWindow();
   int max=(width>h?width:h);
   window *w = windows;

   while (w != NULL)
      {
      if (w->id == win)
         {         
         w->width=width;
         w->height=h;
         w->move_divider=(max/2.0)/ w->camera[2]/-1.0;

         glViewport (0, 0, (GLsizei) max, (GLsizei) max);
         glMatrixMode(GL_PROJECTION);
         glLoadIdentity();

         perspective(90,4/3,0.0001,2000.0);

         /* this brakes zoom!*/         
         /*  glOrtho(-10,10,-10,10, -2000,2000); */

         glMatrixMode (GL_MODELVIEW);
         break;
         }
      w=w->next;
      }
   }

/*This is called when mouse moves over window button pressed (eg. dragging)*/
void mouse_motion ( int x, int y )
   {
   window *w = getCurrentWindow();

   if (w->rotating)
      {
      int dx =x - w->rstartx;
      int dy =y - w->rstarty;

      update_mo(w->rotation_matrix,dx,0,1,0);

      if (glutGetModifiers()==1) /*shift is pressed*/
         update_mo(w->rotation_matrix,dy,0,0,1);
      else
         update_mo(w->rotation_matrix,dy,1,0,0);

      w->rstartx = x;
      w->rstarty = y;

      refresh();
      }

   if (w->moving)
      {
      w->camera[0]+= (x - w->startx)/w->move_divider;
      w->target[0]+= (x - w->startx)/w->move_divider;

      w->camera[1]-= (y - w->starty)/w->move_divider*(w->camera[2]>0?1:-1);
      w->target[1]-= (y - w->starty)/w->move_divider*(w->camera[2]>0?1:-1);

      w->startx = x;
      w->starty = y;
      refresh();
      }
   }

/*This is called when mouse button is pressed*/
void mouse_buttons ( int button, int state, int x, int y )
   {
   window *w = getCurrentWindow();

   if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
      {
      /*this will be usefull
       shift=1
      control=2
      molemmat=3
      */
      // printf("modifiers=%d\n",glutGetModifiers());    
      switch (w->mode)
         {
         case ROTATE_MODE:
            w->rotating = 1;
            w->rstartx = x;
            w->rstarty = y;
            break;
         case MOVING_MODE:            
            w->moving = 1;
            w->startx = x;
            w->starty = y;
            break;
         }
      }
   if ( button == GLUT_LEFT_BUTTON && state == GLUT_UP )
      {
      switch (w->mode)
         {
         case ROTATE_MODE:
            w->rotating = 0;
            break;
         case MOVING_MODE:
            w->moving = 0;
            break;    
         }
      }


   if ( button == GLUT_WHEEL_UP ||  button == GLUT_WHEEL_DOWN)
      {
      int max=(w->width>w->height?w->width:w->height);
      double change=0.5;
      if (button == GLUT_WHEEL_DOWN)
         change*=-1;
      w->camera[2]+=change;
      w->move_divider=(max/-2.0)/w->camera[2];
      refresh();
      }

   // glutSetCursor(GLUT_CURSOR_CROSSHAIR);
   if ( button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN )
      {
      double X,Y;
      /* 10.0 is how many grid is visible to origon...border*/
      X= (10.0/(w->width/2.0)*x  -10.0  + w->camera[0]  ) /w->scale[0]   ;
      Y= (- (10.0/(w->height/2.0)*y -10.0) + w->camera[1])  /w->scale[1]   ;
      add_point(&(w->user_clicked),X,Y,0);
      glutPostRedisplay();
      //printf("X=%lf. Y=%lf\n",X,Y);
      }
}

#define DELTA 0.25f
void keyboard( unsigned char key, int x, int y )
   {
   window *w = getCurrentWindow();

   switch( key )
      {
      case 27:  /*The ESC-button*/
         glutLeaveMainLoop();
/* glutLeaveMainLoop()=
   FREEGLUT_EXIT_IF_NOT_IALISED ( "glutLeaveMainLoop" );
   fgState.ExecState = GLUT_EXEC_STATE_STOP ;
*/
         break;
      case '1':
         update_mo(w->rotation_matrix, -5, 1,0,0 );
         break;
      case '2':
         update_mo(w->rotation_matrix, 5, 1,0,0 );
         break;
      case '3':
         update_mo(w->rotation_matrix, -5, 0,1,0 );
         break;
      case '4':
         update_mo(w->rotation_matrix, 5, 0,1,0 );
         break;
      case '5':
         update_mo(w->rotation_matrix, -5, 0,0,1 );
         break;
      case '6':
         update_mo(w->rotation_matrix, 5, 0,0,1 );
         break;
      case 'z':
         PNGScreenShot(w->width, w->height);
         break;
/*
      //moving camera or target with keyboard
      case 'q': target[0] -= DELTA; break;
      case 'Q': target[0] += DELTA; break;
      case 'w': target[1] -= DELTA; break;
      case 'W': target[1] += DELTA; break;
      case 'e': target[2] -= DELTA; break;
      case 'E': target[2] += DELTA; break;
      case 'a': camera[0] -= DELTA; break;
      case 'A': camera[0] += DELTA; break;
      case 's': camera[1] -= DELTA; break;
      case 'S': camera[1] += DELTA; break;
      case 'd': camera[2] -= DELTA; break;
      case 'D': camera[2] += DELTA; break;
*/
      }
 refresh();
/*is this enough? glutPostRedisplay(); */
}

void aapo_input(int lastKey,char *input)
{
   if ((lastKey == 13) && input[0])
      {
      double d=atof(input);
//whichObject = atoi(inputString) ; // Get the input number

      printf("given double %lf \n",d);
      }

   if (lastKey == 27)
      {
      printf("cancelled\n");
      }

}


void special_keys (int key, int x, int y)  {
   window *w = getCurrentWindow();

    switch (key)
        {
        case GLUT_KEY_F12 :
            printf ("F12 function key. \n");
  
KeyboardInputStart("kysely ikkuna",
                     aapo_input,w->id);

            break;
case GLUT_KEY_F11 :
            printf ("F11 function key. \n");
  
KeyboardInputStart("kysely ikkuna2",
                     aapo_input,w->id);

            break;
        
        case GLUT_KEY_LEFT :
            w->scale[0] -=0.1; refresh();
            break;
        case GLUT_KEY_UP :
            if (glutGetModifiers()==1) /*shift*/
              w->scale[2] +=0.1;
            else
               w->scale[1] +=0.1;
            refresh();
            break;
        case GLUT_KEY_RIGHT :
            w->scale[0] +=0.1;refresh();
            break;
        case GLUT_KEY_DOWN :
             if (glutGetModifiers()==1) /*shift*/
               w->scale[2] -=0.1;
            else
               w->scale[1] -=0.1;
            refresh();
            break;
        case GLUT_KEY_PAGE_UP :
            printf ("Page up directional key. \n");
            break;
        case GLUT_KEY_PAGE_DOWN :
            printf ("Page down directional key. \n");
            break;
        case GLUT_KEY_HOME :
            printf ("Home directional key. \n");
            break;
        case GLUT_KEY_END :
            printf ("End directional key. \n");
            break;
        case GLUT_KEY_INSERT :
            printf ("Inset directional key. \n");
            break;
}
}

void toggle_grid(window *w, int plane) {
      char title[20];
      int menuID=plane+5;
      char *t;
      if (plane==0)
         t="XY";
      else if (plane==1)
         t="YZ";
      else
         t="XZ";
            

      if (w->coordplane[plane])
         {
         w->coordplane[plane]=0;
         sprintf(title,"Show %s-plane",t);         
         }
      else
         {
         w->coordplane[plane]=1;
         sprintf(title,"Hide %s-plane",t);         
         }      
      glutChangeMenuEntryAttributes(menuID,title,menuID);
}



/*
 * A menu callback
 */
void menu_handler( int menuID )
{
  window *w = getCurrentWindow();
    

    /*      debug print     */
    printf( "SampleMenu() callback executed, windowID %d, menuID is %i\n", w->id, menuID );

   if (menuID==ROTATE_MODE)
      {
      w->mode=ROTATE_MODE;
      glutSetCursor(GLUT_CURSOR_CYCLE);
      glutChangeMenuEntryAttributes(ROTATE_MODE,"Moving mode",MOVING_MODE);      
      }

   if (menuID==MOVING_MODE)
      {
      w->mode=MOVING_MODE;
      glutSetCursor(GLUT_CURSOR_INFO);
      glutChangeMenuEntryAttributes(MOVING_MODE,"Rotating mode",ROTATE_MODE);
      }

   if (menuID==1)
      {
      glutSetCursor(GLUT_CURSOR_CROSSHAIR);
      }
   
   if (menuID==2)
      {
      printf("Manual\n\
-------\n\
With Keyboard \n\
    * 1 and 2    :   X-axis stay in place and zy-plane rotates\n\
    * 3 and 4    :   Y-axis stay in place and zx-plane rotates\n\
    * 5 and 6    :   Z-axis stay in place and xy-plane rotates\n\
    * z          :   Take screenshot\n\
    * ESC        :   Close all windows\n\
    * UP/DOWN    :   Scales y-axis\n\
    * LEFT/RIGHT :   Scales x-axis\n\
    * Shitt + UP/DOWN :   Scales z-axis\n\
\n");
    
      }
   if (menuID==3) /*quit*/
      {
      glutLeaveMainLoop();
      }

  if (menuID==4) /*reset view*/
      {
      int max=(w->width>w->height?w->width:w->height);
      int i;
      for (i=0;i<16;i++)
         w->rotation_matrix[i]=0;
      init_rotation_matrix(w->rotation_matrix);
      w->scale[0] = 1;
      w->scale[1] = 1;
      w->scale[2] = 1;
      w->target[0] =  default_target[0];
      w->target[1] =  default_target[1];
      w->target[2] =  default_target[2];
      w->camera[0] =  default_camera[0];
      w->camera[1] =  default_camera[1];
      w->camera[2] =  default_camera[2];
            
      w->move_divider=(max/2.0)/ w->camera[2]/-1.0;
      }
 
   if (menuID==5) 
      {
      toggle_grid(w,0);      
      }
   if (menuID==6) 
      {
      toggle_grid(w,1);      
      }
   if (menuID==7) 
      {
      toggle_grid(w,2);      
      }

   if (menuID<0)  /*function menu pressed*/
      {
      int f_id=   -menuID/1000;
      int action= -menuID%1000;
      
      printf("function %d, action %d\n",f_id,action);

      function_node *function =getFunctionById(f_id);
      if (action==4) 
         function->hidden=1;
 glutPostRedisplay();
      }  
}  



void passive_mouse_motion(int x, int y)
{
 window *w = getCurrentWindow();

/*this is the same than in middle-clicking*/
      w->mouse_x= (10.0/(w->width/2.0)*x  -10.0  + w->camera[0]  ) /w->scale[0]   ;
      w->mouse_y= (- (10.0/(w->height/2.0)*y -10.0) + w->camera[1])  /w->scale[1]   ;
        
  
//printf("%d,%d ja %lf,%lf\n",x,y, w->mouse_x,w->mouse_y);
 glutPostRedisplay();

}






void init_window(int win)
   {
   if (win>numbers_of_windows)
      {
      init_window(win-1); /*recursively. all lower is initialized too*/
      }
 if (win==numbers_of_windows)
   {
   char title[20];
   sprintf(title,"aaPlot Window %d",win);
   numbers_of_windows++;

   add_window (default_window_width, default_window_height, title);
   window *w = windows;

   glutInitWindowSize (w->width, w->height);
   glutInitWindowPosition (0, 0);

   w->id = glutCreateWindow (w->title);
   ogSetIcon();

   glutDisplayFunc  (display);
   glutReshapeFunc  (reshape);
   glutKeyboardFunc (keyboard);
   glutSpecialFunc  (special_keys);
   glutMouseFunc    (mouse_buttons);
   glutMotionFunc   (mouse_motion);

   glutPassiveMotionFunc(passive_mouse_motion);
   

    int grid_sub_menu;
    int subMenuB;

    w->menuID = glutCreateMenu( menu_handler );
    
//    glutAddMenuEntry( "Sub menu A1 (01)", 11 );
  /*  glutAddMenuEntry( "Sub menu A2 (02)", 12 );
    glutAddMenuEntry( "Sub menu A3 (03)", 13 );
*/
    subMenuB = glutCreateMenu( menu_handler );
    glutAddMenuEntry( "Sub menu B1 (04)", 14 );
    glutAddMenuEntry( "Sub menu B2 (05)", 15 );
    glutAddMenuEntry( "Sub menu B3 (06)", 16 );
   
 //subsubmenu glutAddSubMenu( "Going to sub menu A", w->menuID );

grid_sub_menu = glutCreateMenu( menu_handler );

glutAddMenuEntry(w->coordplane[0]?"Hide XY-grid":"Show XY-grid",  5 );
glutAddMenuEntry(w->coordplane[1]?"Hide YZ-grid":"Show YZ-grid",  6 );
glutAddMenuEntry(w->coordplane[2]?"Hide XZ-grid":"Show XZ-grid",  7 );

    glutCreateMenu( menu_handler );
    glutAddMenuEntry( "RotateMode",  ROTATE_MODE );
    glutAddMenuEntry( "Crosshair Cursor",   1 );
    glutAddMenuEntry( "Help", 2 );
    glutAddMenuEntry( "Reset view",  4 );
    glutAddMenuEntry( "Close All (ESC)",  3 );

 
   glutAddSubMenu( "Grids",grid_sub_menu );

   glutAddSubMenu( "Entities", w->menuID );
   //test case glutAddSubMenu( "Enter sub menu B", subMenuB );
   glutAttachMenu( GLUT_RIGHT_BUTTON );





   /*window mode is 'moving' at the start*/
   glutSetCursor(GLUT_CURSOR_INFO);
   }
}




void init_all() {
   if (!(is_initialized))
      {
      int c=1;
      char *v[]={"aaPlot"};
      is_initialized=1;

      /*just something to glutInit*/
      glutInit(&c, v);

      glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH|GLUT_DOUBLE);
      glEnable (GL_DEPTH_TEST);
      glClearColor (0.0, 0.0, 0.0, 0.0);


      /*This helps visualization of surfaces. FIX this better*/
      #define LIGHTS
      #ifdef LIGHTS
         {
         GLfloat pos[4] = {0., -5., 0., 1.};
         GLfloat white[4] = {1., 1., 1., 1.};
         GLfloat black[4] = {0., 0., 0., 0.};

         glEnable (GL_LIGHTING);
         glEnable (GL_COLOR_MATERIAL);
         glColorMaterial (GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

         glEnable (GL_LIGHT1);
         glLightfv (GL_LIGHT1, GL_POSITION, pos);
         glLightfv (GL_LIGHT1, GL_DIFFUSE, white);
         glLightfv (GL_LIGHT1, GL_SPECULAR, black);

         glMaterialfv (GL_FRONT, GL_SPECULAR, black);
         }
      #endif

      /*This is important. Now main-program continues when gl-windows are closed*/
      glutSetOption(505, 2);
      }
}

/*If there are nothing to draw, just continue*/
void drawAll()
   {
   if (is_initialized)
      glutMainLoop();
   }





void changeEntityColor(int id, float red, float green, float blue) {
function_node *n = getFunctionById(id);
if (n==NULL)
   {
   table_node *t =getTableById (id);
   if (t==NULL)
      return;
   t->red = red;
   t->green = green;
   t->blue = blue;
   return;
   }

n->red = red;
n->green = green;
n->blue = blue;
}


void changeEntityPlotSize(int id, int size) {
function_node *n = getFunctionById(id);
if (n==NULL)
   {
   table_node *t =getTableById (id);
   if (t==NULL)
      return;
   t->size = size;
   return;
   }

n->size = size;
}

/*not for tables*/
void changeEntityXStepping(int id, double x_step) {
function_node *n = getFunctionById(id);
if (n==NULL)
   {   
   return;
   }
n->x_step = x_step;
}

/*not for tables
changing z_step of R->R function means nothing
*/
void changeEntityZStepping(int id, double z_step) {
function_node *n = getFunctionById(id);
if (n==NULL)
   {   
   return;
   }
n->z_step = z_step;
}


void changeEntityTitle(int id, char *title) {
function_node *n = getFunctionById(id);
if (n==NULL)
   {
   table_node *t =getTableById (id);
   if (t==NULL)
      return;
   t->name = title;
   return;
   }

n->name = title;
}


/*not ready. just some test */
void setWindowAttribute(int win, char* attrib, double x) {
window *w =get_window_by_int(win);
w->scale[0]=x;

}


/*
reverse ordered. First given point is last in the array.
*/
double *getClickedPointsFromWindow(int win, int *n) {  
   window *w = get_window_by_int(win);


   double *ret;
   int i=0;
   int count=0;
   point *p = w->user_clicked;

   while (p)
      {     
      count++;
      p=p->next;
      }

   *n=count;   
   ret= malloc(2*count*sizeof(double));   
   p = w->user_clicked;
   for (i=0;i<2*count;i=i+2)
      {      
      ret[i]  =p->x;
      ret[i+1]=p->y;
      p=p->next;
      }
 
   return ret;
   }



#define ADD_BEGIN float red, green, blue; \
   window *w; \
   init_all();\
   init_window(win); \
   w=get_window_by_int(win); \
   getColors(&red,&green,&blue);

#define ADD_PUT_MENU int submenu;\
    submenu = glutCreateMenu( menu_handler );\
    glutAddMenuEntry( "Change color", 14 );\
    glutAddMenuEntry( "Change title", 15 );\
    glutAddMenuEntry( "Change stepping", 16 );\
    glutAddMenuEntry( "Toggle hide/unhide", 17 );\
    glutSetMenu(w->menuID);\
    glutAddSubMenu( s, submenu );

void put_menu(int f_id, int menu_id, char *title) {
    int submenu;
    submenu = glutCreateMenu( menu_handler );
    glutAddMenuEntry( "Change color", -(f_id*1000+1) );
    glutAddMenuEntry( "Change title", -(f_id*1000+2) );
    glutAddMenuEntry( "Change stepping", -(f_id*1000+3) );
    glutAddMenuEntry( "Toggle hide/unhide", -(f_id*1000+4) );
    glutSetMenu(menu_id);
    glutAddSubMenu( title, submenu );
}

int addRFunction(int win,double (*func_ptr)(double), double step, char *s)
   {
   ADD_BEGIN
   int f_id = function_add(&(w->functions),func_ptr,step,s,red,green,blue);
   put_menu(f_id,w->menuID,s);
   return f_id;
   }

int addRFunctionWithP(int win,double (*func_ptr)(double,double*),double *para, double step, char *s)
   {
   ADD_BEGIN
   int f_id =function_addB(&(w->functions),func_ptr,para,step,s,red,green,blue);
   put_menu(f_id,w->menuID,s);
   return f_id;
}

int addR2Function(int win,double (*func_ptr)(double,double), double x_step, double z_step, char *s)
   {
   ADD_BEGIN
   int f_id = function_add2(&(w->functions),func_ptr,x_step,z_step,s,red,green,blue);
   put_menu(f_id,w->menuID,s);
   return f_id;
   }

int addR2FunctionWithP(int win,double (*func_ptr)(double,double,double*),double *para, double x_step, double z_step, char *s)
   {
   ADD_BEGIN
   int f_id = function_add2B(&(w->functions),func_ptr,para,x_step,z_step,s,red,green,blue);
   put_menu(f_id,w->menuID,s);
   return f_id;
}

int addRCurve(int win,void (*curve_ptr)(double,double*,double*,double*), double step, double lower, double upper, char *s)
   {
   ADD_BEGIN
   int f_id =  function_add3(&(w->functions),curve_ptr,step,lower,upper,s,red,green,blue);
   put_menu(f_id,w->menuID,s);
   return f_id; 
   }

int addRCurveWithP(int win,void (*curve_ptr)(double,double*,double*,double*,double*),double *para, double step, double lower, double upper, char *s)
   {
   ADD_BEGIN
   int f_id= function_add3B(&(w->functions),curve_ptr,para,step,lower,upper,s,red,green,blue);
   put_menu(f_id,w->menuID,s);
   return f_id;
   }


int addTableDataFile(int win,char *file, char *s)
   {
   ADD_BEGIN
   point *pl=loadFile(file);
   int f_id = add_table(&(w->tables),pl,s,red,green,blue);
   put_menu(f_id,w->menuID,s);
   return f_id;
   }

int addTableDataArrays(int win,int count,double x[],double y[], char *s)
   {
   ADD_BEGIN
   point *pl=makeList(count,x,y);
   int f_id = add_table(&(w->tables),pl,s,red,green,blue);
   put_menu(f_id,w->menuID,s);
   return f_id;
   }
