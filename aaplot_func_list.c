
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
        double lower_alfa;   /*only curves has this*/
        double upper_alfa;   /*only curves has this*/
        int type;
        double *parameters; /*only 'with-parameters' has this*/
        double size;        /*size of the plots*/
        double x_step;
        double z_step;
        float red;
        float green;
        float blue;
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

11=R->R, with parameters
12= R2->R, with parameters
13= R->R3, with parameters
*/


#define MALLOC function_node *n = (function_node *)malloc(sizeof(function_node));\
    if (n == NULL)\
      { \
      printf("memory allocation failed\n");\
      return -1;\
      }

#define GENERAL n->next = *functions;\
      *functions = n;\
      n->size = default_size;\
      n->x_step = x_step;\
      n->name = s;\
      n->red = red;\
      n->green = green;\
      n->blue = blue;\
      n->id=entity_id_counter;\
      entity_id_counter++;\

/*Add node to the first of the list.
Returns id-number of the new node. Or -1 in the error situation.
*/
int function_add(function_node **functions, double (*func_ptr)(double), double x_step, char* s,float red, float green, float blue) {
MALLOC
GENERAL

n->function=func_ptr;
n->type=1;
return n->id;
}

int function_addB(function_node **functions, double (*func_ptr)(double,double*),double *para, double x_step, char* s,float red, float green, float blue) {
MALLOC
GENERAL

n->function_p=func_ptr;
n->type=11;
n->parameters=para;
return n->id;
}


int function_add2(function_node **functions, double (*func_ptr)(double,double), double x_step, double z_step, char* s,float red, float green, float blue) {
MALLOC
GENERAL

      n->function2=func_ptr;
      n->z_step = z_step;
      n->type=2;

return n->id;
}

int function_add2B(function_node **functions, double (*func_ptr)(double,double,double*),double *para, double x_step, double z_step, char* s,float red, float green, float blue) {
MALLOC
GENERAL

      n->function2_p=func_ptr;
      n->z_step = z_step;
      n->type=12;
      n->parameters=para;
return n->id;
}


/*stepping is x_stepping*/
int function_add3(function_node **functions, void (*curve_ptr)(double,double*,double*,double*),double x_step, double lower, double upper,char* s,float red, float green, float blue) {
MALLOC
GENERAL

      n->type=3;
      n->curve=curve_ptr;
      n->lower_alfa = lower;
      n->upper_alfa = upper;
    return n->id;
}

int function_add3B(function_node **functions, void (*curve_ptr)(double,double*,double*,double*,double*),double *para, double x_step, double lower, double upper,char* s,float red, float green, float blue) {
MALLOC
GENERAL

      n->type=13;
      n->curve_p=curve_ptr;
      n->lower_alfa = lower;
      n->upper_alfa = upper;
      n->parameters=para;
    return n->id;
}


#ifdef not_yet_tested_and_too_old
void list_remove(node *functions,int id) {
   node *n = functions;
   node *edellinen = functions;
   if (n == NULL)
      {
      /*printf("list is empty\n");*/
      return;
      }

   /*removing the first is special case   */
   if (n->id==id)
      {
      functions=n->next;
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


void list_removeB(node *functions, double (*f)(double)) {
   node *n = functions;
   node *edellinen = functions;
   if (n == NULL)
      {
      /*printf("list is empty\n");*/
      return;
      }

   /*removing the first is special case   */
   if (n->function==f)
      {
      functions=n->next;
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

/* //testing
double f(double x) {
return x*2;
}

double g(double x) {
return x*x;
}


double h(double x) {
return x+2;
}

int main(void) {
list_print();
//list_add(f,-5,5);
list_add(g,-5,5);
list_print();
list_add(h,-5,5);

//    list_print(functions);
   // list_remove(&functions);
//    list_remove(&functions);
list_print();

 //tamakin toimii list_removeB(g);
list_remove(0);
list_print();
list_add(g,-5,5);
list_print();

//  list_remove(&functions);

    return 0;
}
*/
