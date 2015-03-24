
/*
Linked list.
Each node contains
-some sort of function
-type
-plot_size
-stepping (and ranges if curve)
-color
-id_number
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

typedef struct ns {
         double (*function) (double);
         double (*function_p) (double,double*); /*function with parameters*/
         double (*function2) (double,double);
         double (*function2_p) (double,double,double*);  /*function with parameters*/
         void (*curve)   (double,double*,double*,double*);
         void (*curve_p)   (double,double*,double*,double*,double*); /*curve with parameters*/
         void (*curve2)   (double,double,double*,double*,double*); /*surface */
         void (*curve2_p)   (double,double,double*,double*,double*,double*); /*surface with parameters*/

         double lower_alfa;   /*only curve has this*/
         double upper_alfa;   /*only curve has this*/
         double lower_beta;   /*only curve-surface has this*/
         double upper_beta;   /*only curve-surface has this*/


         int type;
         double *parameters; /*only 'with-parameters' has this*/
         double size;        /*size of the plots*/
         double step_0;
         double step_1;
         float red;
         float green;
         float blue;

         int hidden;
         int direction[3];
         int id;
         char *name;
         struct ns *next;
} function_node;

int entity_id_counter=0;
/*
type means:
1= R->R
2= R2->R
3= R->R3
4= R2 ->R3

11=R->R, with parameters
12= R2->R, with parameters
13= R->R3, with parameters
14= R2 ->R3, with parameters
*/


#define MALLOC function_node *n = malloc(sizeof(function_node));\
    if (n == NULL)\
      { \
      /*  printf("memory allocation failed\n");*/     \
      return -1;\
      }

#define GENERAL n->next = *functions;\
      *functions = n;\
      n->size = default_size;\
      n->step_0 = step_0;\
      n->name = s;\
      n->red = red;\
      n->green = green;\
      n->blue = blue;\
      n->hidden = 0;\
      n->direction[0] = 0;\
      n->direction[1] = 1;\
      n->direction[2] = 2;\
      n->id=entity_id_counter;\
      entity_id_counter++;\

/*Add node to the first of the list.
Returns id-number of the new node. Or -1 in the error situation.
*/
int function_add(function_node **functions, double (*func_ptr)(double), double step_0, char* s,float red, float green, float blue) {
MALLOC
GENERAL

n->function=func_ptr;
n->type=1;
return n->id;
}

int function_addB(function_node **functions, double (*func_ptr)(double,double*),double *para, double step_0, char* s,float red, float green, float blue) {
MALLOC
GENERAL

n->function_p=func_ptr;
n->type=11;
n->parameters=para;
return n->id;
}


int function_add2(function_node **functions, double (*func_ptr)(double,double), double step_0, double step_1, char* s,float red, float green, float blue) {
MALLOC
GENERAL

      n->function2=func_ptr;
      n->step_1 = step_1;
      n->type=2;

return n->id;
}

int function_add2B(function_node **functions, double (*func_ptr)(double,double,double*),double *para, double step_0, double step_1, char* s,float red, float green, float blue) {
MALLOC
GENERAL

      n->function2_p=func_ptr;
      n->step_1 = step_1;
      n->type=12;
      n->parameters=para;
return n->id;
}



int curve_add(function_node **functions, void (*curve_ptr)(double,double*,double*,double*),double step_0, double lower, double upper,char* s,float red, float green, float blue) {
MALLOC
GENERAL

      n->type=3;
      n->curve=curve_ptr;
      n->lower_alfa = lower;
      n->upper_alfa = upper;
    return n->id;
}

int curve_addB(function_node **functions, void (*curve_ptr)(double,double*,double*,double*,double*),double *para, double step_0, double lower, double upper,char* s,float red, float green, float blue) {
MALLOC
GENERAL

      n->type=13;
      n->curve_p=curve_ptr;
      n->lower_alfa = lower;
      n->upper_alfa = upper;
      n->parameters=para;
    return n->id;
}


int curve2_add(function_node **functions, void (*curve_ptr)(double,double,double*,double*,double*),double step_0, double step_1, double lowerA, double upperA,double lowerB, double upperB,char* s,float red, float green, float blue) {
MALLOC
GENERAL

      n->type=4;
      n->curve2=curve_ptr;
      n->step_1=step_1;
      n->lower_alfa = lowerA;
      n->upper_alfa = upperA;
      n->lower_beta = lowerB;
      n->upper_beta = upperB;
    return n->id;
}

int curve2_addB(function_node **functions, void (*curve_ptr)(double,double,double*,double*,double*,double*),double *para, double step_0, double step_1, double lowerA, double upperA,double lowerB, double upperB,char* s,float red, float green, float blue) {
MALLOC
GENERAL

      n->type=14;
      n->curve2_p=curve_ptr;
      n->step_1=step_1;
      n->lower_alfa = lowerA;
      n->upper_alfa = upperA;
      n->lower_beta = lowerB;
      n->upper_beta = upperB;

      n->parameters=para;
    return n->id;
}

