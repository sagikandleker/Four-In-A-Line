#include <stdio.h>
#include "Stack.h"

void Stack_Init(Stack *S)
{
    S->size = 0;
}

int Stack_Top(Stack *S)
{
    if (S->size == 0) {
        //fprintf(stderr, "Error: stack empty\n");
        return -1;
    } 

    return S->data[S->size-1];
}

void Stack_Push(Stack *S, int d)
{
    if (S->size < STACK_MAX)
        S->data[S->size++] = d;
    else
        fprintf(stderr, "Error: stack full\n");
}

void Stack_Pop(Stack *S)
{
    if (S->size == 0)
        fprintf(stderr, "Board is empty - can't undo!\n");
    else
        S->size--;
}

int Stack_Full(Stack* s)
{
    if(s->size == STACK_MAX)
    {
        return 1;
    }
    else
        return 0;
}

int Stack_Size(Stack* s)
{
    return (s->size);
}