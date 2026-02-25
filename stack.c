// Stack implementation
//
#include "stack.h"

#define MAX_SIZE	10000

Stack* stack_create(int size){
	if(size> MAX_SIZE)
		return NULL;
	Stack * s=(Stack *) malloc(sizeof(Stack));
	s->a =(int *) malloc(sizeof(int) * size);
	s->size = size;
	s->top = -1;
    return s;
}

void stack_delete(Stack *s){
	if(s == NULL)
		return;
	free(s->a);
	free(s);
}


bool stack_isEmpty(Stack *s){
	if( (s!= NULL) && (s->top == -1))//empty
		return true;
	return false;
}

bool stack_isFull(Stack *s){
	if( (s!= NULL) && (s->top ==  (s->size -1)))//stack full 
		return true;
	return false;
}

int stack_push(Stack * s, int val){// 0 success  -1 failure
    if(s == NULL)
		return -1;
	if(stack_isFull(s))//stack full
		return -1;
	s->top++;
	s->a[s->top]=val;
	return 0;
}

int stack_pop(Stack * s){
  if(s == NULL)
		return INT_MIN;
	if(stack_isEmpty(s))//stack empty 
		return INT_MIN;
	int r= s->a[s->top];
	s->top--;
	return r;
}

int stack_peek(Stack *s){
	if(s == NULL)
		return INT_MIN;
	if(stack_isEmpty(s))//stack empty 
		return INT_MIN;
	return s->a[s->top];
}

void stack_print(Stack *s){
	if(s == NULL)
		printf("Invalid stack !!\r\n");
	if( s->top==-1)
		printf("Empty stack  !!\r\n");

	int i = s->top;
	while(i>-1){
    printf( " %d ", s->a[i]);
    i--;
    }
    printf("\n");
}


/* use example
int main()
{
    Stack * s= stack_create(20);
    stack_push(s, 50);
    stack_push(s, 10);
    stack_push(s, 20);
    stack_push(s, 40);
    stack_push(s, 30);
    stack_push(s, 1);
    stack_push(s, 5);
    
    printf("Stack s = ");
    stack_print(s);
    
    printf("top of stack:");
    printf(" %d \n", stack_peek(s));
    printf("pop element from stack :");
    printf(" %d \n", stack_pop(s));
    printf("top of stack :");
    printf(" %d \n", stack_peek(s));
    stack_push(s, 100);
    printf("Stack s = ");
    stack_print(s);
    stack_delete(s);
    
    return 0;
}
*/
