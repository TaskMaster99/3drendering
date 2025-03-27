#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <string.h>

#define MAX_SIZE_STACK 512

/**
 * Stack
 * @param array pointer to the stack
 * @param top id to the top of the stack
 */
typedef struct Stack
{
    void* array[MAX_SIZE_STACK];
    int top;
} __attribute__((aligned(64))) Stack;
/**
 * push
 * @param stck pointer to the stack
 * @param addr element to push
 */
void push(Stack* stck, void* addr)
{
    if((stck->top + 1) < MAX_SIZE_STACK)
    {
        stck->array[stck->top] = addr;
        stck->top++;
    }
}
/**
 * pop
 * @param stck element popped from the stack
 */
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