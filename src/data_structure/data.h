#ifndef DATA_H
#define DATA_H

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
void reserve(D_Array* vec, unsigned int nb_element, unsigned int size_type);
/**
 * push an element at the end of the array
 * @param vec the dynamic array
 * @param element the element to be pushed
 */
void push_back(D_Array* vec, void* element);
/**
 * get the pointer to the array
 * @param vec the dynamic array
 * @return the pointer to the array
 */
void* data(D_Array* vec);
/**
 * free the memory taken by the array
 * @param vec the dynamic array
 */
void clean(D_Array* vec);

#endif