#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define MAX 25

typedef int EType;		// type of elements in stack
typedef int BOOLEAN;

typedef struct {
  EType data[MAX];
  int top;
} STACK;

void initialize(STACK *pS) 	// initialze the stack	
{
  pS->top = -1;
}

BOOLEAN isEmpty(STACK *pS) 	// returns true if the stack is empty
{
  return pS->top == -1;
}

BOOLEAN isFull(STACK *pS)  	// returns true if the stack is full
{
 return pS->top == MAX-1;
}

BOOLEAN pop(STACK *pS, EType *px)	// removes the top element from the stack 
{					// has px point to the removed element   // returns true if done successfully       
  if(!isEmpty(pS)){
    *px = pS->data[pS->top--];
    return TRUE; 
  }
  return FALSE;
}

BOOLEAN push(EType x, STACK *pS)	// puts an element on the top of the stack  // returns true if done successfully  
{					
  if(!isFull(pS)){
    pS->data[++(pS->top)] = x;
    return TRUE;
  }

  return FALSE;
}

int main ()
{
  STACK s;
  int i, n;

  initialize (&s);

  for (i=0; i<10; i++)
    push (i, &s);

  while ( !isEmpty(&s) )
  {	
    pop(&s, &n);
    printf("%d \n", n);
  }
  return 0;
}
