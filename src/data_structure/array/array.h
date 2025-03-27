#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>
#include <string.h>

/**
 * Dynamic Array (or vector)
 * @param size_type the size in bytes of the data type stored in the array
 * @param size the size of the array
 * @param capacity the capacity of the array which is always superior to the size of the array
 * @param data the pointer to the generic data
 */
typedef struct D_Array
{
    unsigned int size_type;
    unsigned int size;
    unsigned int capacity;

    void** data;
}D_Array;

/**
 * reserve a chunck of data
 * @param vec the dynamic array
 * @param nb_element the number of element you want allocate
 * @param size_type the size of types you wants for your dynamic array
 */
void reserve(D_Array* vec, unsigned int nb_element, unsigned int size_type)
{   
    vec->size = (nb_element ^ 0x0);
    vec->capacity = vec->size + 5;
    vec->size_type = size_type;
    vec->data = malloc(vec->capacity * sizeof(void*));
}

/**
 * push an element at the end of the array
 * @param vec the dynamic array
 * @param element the element to be pushed
 */
void push_back(D_Array* vec, void* element)
{

    if((vec->size + 1) > vec->capacity)
    {
        vec->size += 1;
        vec->capacity = vec->size + 5;
        vec->data = realloc(vec->data, vec->capacity * sizeof(void*));
    }
    else
    {
        vec->size += 1;
    }

    vec->data[vec->size - 1] = element;
}

/**
 * get the pointer to the array
 * @param vec the dynamic array
 * @return the pointer to the array
 */
void* data(D_Array* vec)
{
    return vec->data;
}

/**
 * free the memory taken by the array
 * @param vec the dynamic array
 */
void clean(D_Array* vec)
{
    free(vec->data);
}

#endif
