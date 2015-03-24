 #include <setjmp.h>


typedef struct tagSOG_State SOG_State;
struct tagSOG_State
{
int eka;
jmp_buf aapo; 
int vip;
};


 
int main() {
#ifdef asfad
# if __WORDSIZE == 64
typedef long int __jmp_buf[8];
# else
typedef int __jmp_buf[6];
# endif



/* Calling environment, plus possibly a saved signal mask.  */
struct __jmp_buf_tag
  {
    /* NOTE: The machine-dependent definitions of `__sigsetjmp'
       assume that a `jmp_buf' begins with a `__jmp_buf' and that
       `__mask_was_saved' follows it.  Do not move these members
       or add others before it.  */
    __jmp_buf __jmpbuf;         /* Calling environment.  */
    int __mask_was_saved;       /* Saved the signal mask?  */
    __sigset_t __saved_mask;    /* Saved signal mask.  */
  };


__BEGIN_NAMESPACE_STD

typedef struct __jmp_buf_tag jmp_buf[1];
#endif

jmp_buf aaa;

/*=

{{0}},
{0},
{0}

;
*/


int e,v;
SOG_State ogState =
{
e,
{{{0}}},


v};


return 0;
}
