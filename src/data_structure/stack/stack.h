#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <string.h>

#define MAX_SIZE_STACK 512

typedef struct Stack
{
    void* array[MAX_SIZE_STACK];
    int top;
} __attribute__((aligned(64))) Stack;

void push(Stack* stck, void* addr)
{
    if((stck->top + 1) < MAX_SIZE_STACK)
    {
        stck->array[stck->top] = addr;
        stck->top++;
    }
}

void* pop(Stack* stck)
{
    void* tmp = NULL;
    if((stck->top - 1) > -1)
    {
        tmp = stck->array[stck->top - 1];
        stck->array[stck->top --] = NULL;
    }
    return tmp;
}

#endif