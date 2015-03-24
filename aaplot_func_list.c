#define DISCRET 1
#define CONTINUOS 2

/*
fix. dimension 
1= R->R
2= R2->R
3= R->R3

11=R->R, with parameters
*/

/*
Linked list.
Node contains
-function
-ehka noita rajoja
-id-number

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
void (*curve_p)   (double,double*,double*,double*,double*); /*function with parameters*/
        double lower_alfa;  /*only curves has this*/
        double upper_alfa;  /*only curves has this*/
        int dimension;
        int type; /*DISCRET / CONTINUOS */
        double *parameters; /*only if it has*/
        double size;
        double x_step;
        double z_step;
        float red;
        float green;
        float blue;
        int id;
        char *name;
        struct ns *next;
} node;

int id_counter=0;

#define MALLOC node *n = (node *)malloc(sizeof(node));\
    if (n == NULL)\
      { \
      printf("muistin varaus epaonnistui\n");\
      return -1;\
      }\

#define YHTEISET n->next = *funktiot;\
      *funktiot = n;\
      n->size = size;\
      n->x_step = x_step;\
      n->name = s;\
      n->red = red;\
      n->green = green;\
      n->blue = blue;\
      n->id=id_counter;\
      id_counter++;\

/*Add node to the first of the list.
Returns id-number of the new node. Or -1 in the error situation.
*/
int list_add(node **funktiot, double (*func_ptr)(double),int type,double size, double x_step, char* s,float red, float green, float blue) {
MALLOC
YHTEISET

n->function=func_ptr;
n->type=type;
n->dimension=1;
return n->id;
}

int list_addB(node **funktiot, double (*func_ptr)(double,double*),double *para,int type,double size, double x_step, char* s,float red, float green, float blue) {
MALLOC
YHTEISET

n->function_p=func_ptr;
n->type=type;
n->dimension=11;
n->parameters=para;
return n->id;
}


int list_add2(node **funktiot, double (*func_ptr)(double,double),double size, double x_step, double z_step, char* s,float red, float green, float blue) {
MALLOC
YHTEISET

      n->function2=func_ptr;
      n->z_step = z_step;
      n->dimension=2;
      n->type=DISCRET;

return n->id;
}

int list_add2B(node **funktiot, double (*func_ptr)(double,double,double*),double *para,double size, double x_step, double z_step, char* s,float red, float green, float blue) {
MALLOC
YHTEISET

      n->function2_p=func_ptr;
      n->z_step = z_step;
      n->dimension=12;
      n->type=DISCRET;
      n->parameters=para;
return n->id;
}


/*stepping is x_stepping*/
int list_add3(node **funktiot, void (*curve_ptr)(double,double*,double*,double*),double size, double x_step, double lower, double upper,char* s,float red, float green, float blue) {
MALLOC
YHTEISET

      n->dimension=3;
      n->type=DISCRET;
      n->curve=curve_ptr;
      n->lower_alfa = lower;
      n->upper_alfa = upper;
    return n->id;
}

int list_add3B(node **funktiot, void (*curve_ptr)(double,double*,double*,double*,double*),double *para,double size, double x_step, double lower, double upper,char* s,float red, float green, float blue) {
MALLOC
YHTEISET

      n->dimension=13;
      n->type=DISCRET;
      n->curve_p=curve_ptr;
      n->lower_alfa = lower;
      n->upper_alfa = upper;
      n->parameters=para;
    return n->id;
}



void list_remove(node *funktiot,int id) {
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


void list_removeB(node *funktiot, double (*f)(double)) {
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

/* //testailu
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

//    list_print(funktiot);
   // list_remove(&funktiot);
//    list_remove(&funktiot);
list_print();

 //tamakin toimii list_removeB(g);
list_remove(0);
list_print();
list_add(g,-5,5);
list_print();

//  list_remove(&funktiot);

    return 0;
}
*/
