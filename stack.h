

// Stack implementation
//
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_SIZE	10000

typedef struct stack_type{
	int* a;
	int top;
  int size;
}Stack;

Stack* stack_create(int size):

void stack_delete(Stack *s):

bool stack_isEmpty(Stack *s):

bool stack_isFull(Stack *s):

int stack_push(Stack * s, int val):

int stack_pop(Stack * s):

int stack_peek(Stack *s):

void stack_print(Stack *s):
