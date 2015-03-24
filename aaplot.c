
void refresh ();
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "aaplot_defaults.c"




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





#if !defined(GLUT_WHEEL_UP)
#  define GLUT_WHEEL_UP   3
#  define GLUT_WHEEL_DOWN 4
#endif
/*
joitain linkkeja
http://www.opengl.org/documentation/specs/glut/spec3/node1.html
http://nehe.gamedev.net/data/lessons/lesson.asp?lesson=13
*/
/*GLOBALS*/

int is_initialized = 0;
extern window *windows;


/* piirtaa piin kolmella tikulla
void pii(double x){
   glLineWidth(2.0);
   glBegin(GL_LINES);

   glColor3f(1,1,1);

   glVertex3f(x-0.2,-0.3,0);
   glVertex3f(x+0.2,-0.3,0);
    glVertex3f(x-0.09,-0.3,0);
    glVertex3f(x-0.09,-0.6,0);
   glVertex3f(x+0.09,-0.3,0);
   glVertex3f(x+0.09,-0.6,0);

   glEnd();

}
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


/*ikkuna buildaa vain itseaan*/
void buildModel( window *w )
   {

glClearColor(w->background_color[0],
             w->background_color[1],
             w->background_color[2],
                           0);
glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   glPushMatrix();

   /*Akselit*/
   glLineWidth(width_of_the_axis);
   glBegin(GL_LINES);
   /*punaisella x-akseli*/
   glColor3f(1,0,0);
   glVertex3f(lower_x_limit,0,0);
   glVertex3f(upper_x_limit,0,0);

   /*vihrealla y-akseli*/
   glColor3f(0,1,0);
   glVertex3f(0,lower_y_limit,0);
   glVertex3f(0,upper_y_limit,0);

   /*sinisella z-akseli*/
   glColor3f(0,0,1);
   glVertex3f(0,0,lower_z_limit);
   glVertex3f(0,0,upper_z_limit);
   glEnd();


 /*ruudukko*/
if (y_ruudukko)
   {
   double x;
   for (x=lower_x_limit;x<upper_x_limit;x=x+y_ruudukko)
      {
      glLineWidth(1.0);
      glColor3f(0.5,0.5,0.5);
      glBegin(GL_LINES);
      glVertex3f(x,upper_y_limit,0);
      glVertex3f(x,lower_y_limit,0);
      glVertex3f(-x,upper_y_limit,0);
      glVertex3f(-x,lower_y_limit,0);
      glEnd();
      }
   }

if (x_ruudukko)
   {
   double y;
   for (y=lower_y_limit;y<upper_y_limit;y=y+x_ruudukko)
      {
      glLineWidth(1.0);
      glColor3f(0.5,0.5,0.5);
      glBegin(GL_LINES);
      glVertex3f(upper_x_limit,y,0);
      glVertex3f(lower_x_limit,y,0);
      glVertex3f(upper_x_limit,-y,0);
      glVertex3f(lower_x_limit,-y,0);
      glEnd();
      }
   }



/* //asteikko=pienet nysat siis vain, et tarvitse, jos ruudukko nakyy
double tappi=0.1;
double x,y;
for (x=M_PI;x<upper_x_limit;x=x+M_PI)
   {
   glBegin(GL_LINES)
   glColor3f(1,0,0);
   glVertex3f(x,tappi,0);
   glVertex3f(x,-tappi,0);
   glVertex3f(-x,tappi,0);
   glVertex3f(-x,-tappi,0);
 glEnd();
}
for (y=1;y<upper_y_limit;y=y+1)
   {
glColor3f(0,1,0);
glBegin(GL_LINES);

   glVertex3f(tappi,y,0);
   glVertex3f(-tappi,y,0);
   glVertex3f(tappi,-y,0);
   glVertex3f(-tappi,-y,0);
 glEnd();
}

*/

#ifdef akselienNuolet
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



/*akselit valmiit////////////////*/
/*///////////////////////////////*/


/*  funktiot   ////////////////*/
/*///////////////////////////////*/
{
  node *n = w->funktiot;
int lkm=0;
while (n != NULL)
   {
   double j,j2;
   double y,y2;
   double i;
   int parameters=0; /*WithParameters-version*/
   glPointSize(n->size);
   glColor3f(n->red,n->green,n->blue);


if (n->dimension>10) 
   {
   parameters=1;
   }


/* R->R  ////////////////*/
if (n->dimension%10==1)
   {
   for (j=lower_x_limit;j<upper_x_limit;j=j+n->x_step)
      {
      y=     parameters==0 ? n->function(j)   :  n->function_p(j,n->parameters);
      if (y>=lower_y_limit && y<=upper_y_limit)
       {
       j2=j;
       while(j2<upper_x_limit)
         {
         j2+=n->x_step;
         y2=   parameters==0 ? n->function(j)  :  n->function_p(j,n->parameters);
         if (y2>=lower_y_limit && y2<=upper_y_limit)
            {
            if (n->type==CONTINUOS)
               glBegin(GL_LINE);
            else
               glBegin(GL_POINTS);

            glVertex3f(j,y,0);
            glVertex3f(j2,y2,0);
            glEnd();
            j2=upper_x_limit; /*break*/
            }
         }
        }
      }
   }

/* funktiot R^2->R   */
if (n->dimension%10==2) 
{
glBegin(GL_POINTS);
 for (i=lower_z_limit;i<upper_z_limit;i=i+n->z_step)
      {
     for (j=lower_x_limit;j<upper_x_limit;j=j+n->x_step)
        {
        y=   parameters==0 ? n->function2(j,i)  :  n->function2_p(j,i,n->parameters);
        if (y>=lower_y_limit && y<=upper_y_limit)
          glVertex3f(j,y,i);
        }
      }
glEnd();
}

/* curves R -> R^3  */
if (n->dimension%10==3) 
{
double alfa;
double x,y,z;
glBegin(GL_POINTS);
for (alfa=n->lower_alfa;alfa < n->upper_alfa;alfa=alfa+n->x_step)
    {
    parameters==0 ?  n->curve(alfa,&x,&y,&z)  :  n->curve_p(alfa,&x,&y,&z,n->parameters);
    if (x>=lower_x_limit && x<=upper_x_limit &&
        y>=lower_y_limit && y<=upper_y_limit &&
        z>=lower_z_limit && z<=upper_z_limit)
        glVertex3f(x,y,z);
    }
glEnd();
}

   draw_text(1, lkm,n->name,n->red,n->green,n->blue);
   lkm++;
   n = n->next;
   }
}
/*  funktiot valmiit  *********/
/******************************/

/*Taulukko datat*/
/*************************************/
table *t = w->taulukot;
while (t != NULL)
   {
   point *p = t->pisteet;
   glPointSize(t->size);
   glColor3f(t->red,t->green,t->blue);   
   glBegin(GL_POINTS); 
   while (p != NULL)
      {
      double x=p->x;
      double y=p->y;
      double z=p->z;
      if (x>lower_x_limit && x<upper_x_limit 
      &&  y>lower_y_limit && y<upper_y_limit 
      &&  z>lower_z_limit && z<upper_z_limit )
         glVertex3f(x,y,z);
      p=p->next;
      }
   glEnd();

   /*maybe? draw_text(1, 1,n->name,n->red,n->green,n->blue);*/
   t = t->next;
   }
}



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
      gluLookAt(w->camera[0], w->camera[1], w->camera[2],
                w->target[0], w->target[1], w->target[2],
                0.0, 1.0, 0.0);
      glMultMatrixf(w->rotation_matrix);    /*rotating */
      buildModel(w);
      }
   w=w->next;   
   }  

 
 glutSwapBuffers();
   }



void reshape(int width, int h)
   {
   int max=(width>h?width:h);
   int win = glutGetWindow();


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

   gluPerspective(90,4/3,1.5,20.0);
   glMatrixMode (GL_MODELVIEW);
 
    
   }  
  w=w->next;  
   }
}

void motion ( int x, int y )
   {
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


   if (w->rotating)
      {
      int dx =x - w->rstartx;
      int dy =y - w->rstarty;

      update_mo(w->rotation_matrix,dx,0,1,0);
      update_mo(w->rotation_matrix,dy,1,0,0);

      /*not-implemented   update_mo(dz, 0,0,1);*/

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


void mouse ( int button, int state, int x, int y )
   {
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


   if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
      {
      w->moving = 1;
      w->startx = x;
      w->starty = y;
      }
   if ( button == GLUT_LEFT_BUTTON && state == GLUT_UP )
      w->moving = 0;

   if ( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN )
      {
      w->rotating = 1;
      w->rstartx = x;
      w->rstarty = y;
      }
   if ( button == GLUT_RIGHT_BUTTON && state == GLUT_UP )
      w->rotating = 0;


   if ( button == GLUT_WHEEL_UP ) /*fix, naiden yhdistaminen*/
      {
      int max=(w->width>w->height?w->width:w->height);
      w->camera[2]+=0.5;
      w->move_divider=(max/-2.0)/w->camera[2];
      refresh();
      }
   if ( button == GLUT_WHEEL_DOWN )
      {
      int max=(w->width>w->height?w->width:w->height);
      w->camera[2]-=0.5;
      w->move_divider=(max/-2.0)/w->camera[2];
      refresh();
      }
/*
if ( button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN )
*/
   
   }

#define DELTA 0.25f
void keyboard( unsigned char key, int x, int y )
   {
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

   switch( key )
      {
      case 27:
         glutLeaveMainLoop();
/*tallaista tuo funktio pitaa sisallaan
FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutLeaveMainLoop" );
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
}

void special_keys (int key, int x, int y)
{  switch (key)
    {

  case GLUT_KEY_F12 :
            printf ("F12 function key. \n");
            break;
        case GLUT_KEY_LEFT :
            printf ("Left directional key. \n");
            break;
        case GLUT_KEY_UP :
            printf ("Up directional key. \n");
            break;
        case GLUT_KEY_RIGHT :
            printf ("Right directional key. \n");
            break;
        case GLUT_KEY_DOWN :
            printf ("Down directional key. \n");
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



  

int ikkunoiden_maara=0;
/*
maara=0
pyydetty. 0,1,2,3,4

*/



void init_window(int win) 
{

 if (win>ikkunoiden_maara)
   {
   init_window(win-1); /*rekursiivisesti myos kaikki pienemmat alustetaan*/
   }
 if (win==ikkunoiden_maara)
{


float  camera[3],target[3];
   target[0] = 0;
   target[1] = 4.0;
   target[2] = 0;
   camera[0] = 0;
   camera[1] = 4.0;
   camera[2] = 10;

char title[20];
sprintf(title,"aaPlot Window %d",win);
ikkunoiden_maara++;

list3_add( camera, target,default_window_width, default_window_height, title); 
window *w = windows;

   glutInitWindowSize (w->width, w->height);
   glutInitWindowPosition (0, 0);

 w->id = glutCreateWindow (w->title);
   
   glutDisplayFunc  (display);
   glutReshapeFunc  (reshape);
   glutKeyboardFunc (keyboard);
   glutSpecialFunc  (special_keys);   
   glutMouseFunc    (mouse);
   glutMotionFunc   (motion);
}

}


void init_all() {
 if (!(is_initialized))
   {
   int c=1;
   char *v[]={"aaPlot"};
   is_initialized=1;

  /*jotakin on annettava tuolle initille*/   
   glutInit(&c, v);

   glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH|GLUT_DOUBLE);
 glEnable (GL_DEPTH_TEST);
   glClearColor (0.0, 0.0, 0.0, 0.0);
  


#define valot
#ifdef valot
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

/*tama on sen takia, etta ikkunoiden sulkeminen jatkaa ohjelmaa*/
glutSetOption(505, 2);              

}
}

void drawAll()
   {
   glutMainLoop();
   }

window *getCurrentWindow(int win)
   {
   window *w = windows;
   int i;
   for (i=0;i<ikkunoiden_maara-win-1;i++)
      {
      w=w->next;
      }
   return w;
   }


#define ADD_BEGIN init_all();\
   window *w; \
   init_window(win); \
   w=getCurrentWindow(win);\

void addRFunction(int win,double (*func_ptr)(double),int type,double size, double step, char *s,float red, float green, float blue)
   {
   ADD_BEGIN
   list_add(&(w->funktiot),func_ptr,type,size,step,s,red,green,blue);
   }

void addRFunctionWithP(int win,double (*func_ptr)(double,double*),double *para,int type,double size, double step, char *s,float red, float green, float blue)
   {
   ADD_BEGIN
   list_addB(&(w->funktiot),func_ptr,para,type,size,step,s,red,green,blue);
   }

void addR2Function(int win,double (*func_ptr)(double,double),double size, double x_step, double z_step, char *s,float red, float green, float blue)
   {
   ADD_BEGIN
   list_add2(&(w->funktiot),func_ptr,size,x_step,z_step,s,red,green,blue);
   }

void addR2FunctionWithP(int win,double (*func_ptr)(double,double,double*),double *para,double size, double x_step, double z_step, char *s,float red, float green, float blue)
   {
   ADD_BEGIN
   list_add2B(&(w->funktiot),func_ptr,para,size,x_step,z_step,s,red,green,blue);
   }

void addRCurve(int win,void (*curve_ptr)(double,double*,double*,double*), double size, double step, double lower, double upper, char *s,float red, float green, float blue)
   {
   ADD_BEGIN
   list_add3(&(w->funktiot),curve_ptr,size,step,lower,upper,s,red,green,blue);
   }

void addRCurveWithP(int win,void (*curve_ptr)(double,double*,double*,double*,double*),double *para, double size, double step, double lower, double upper, char *s,float red, float green, float blue)
   {
   ADD_BEGIN
   list_add3B(&(w->funktiot),curve_ptr,para,size,step,lower,upper,s,red,green,blue);
   }


void addTableDataFile(int win,char *file,double size, char *s,float red, float green, float blue)
   {
   ADD_BEGIN
   point *pl=loadFile(file);
   add_table(&(w->taulukot),pl,size,s,red,green,blue);
   }

void addTableDataArrays(int win,int count,double x[],double y[],double size, char *s,float red, float green, float blue)
   {
   ADD_BEGIN
   point *pl=teeJono(count,x,y);
   add_table(&(w->taulukot),pl,size,s,red,green,blue);
   }

