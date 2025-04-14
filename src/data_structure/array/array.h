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

#define Vector(__TYPE__) \
struct D_Array_##__TYPE__\
{\
    __TYPE__*    full_data;\
    unsigned int size_type;\
    unsigned int size;\
    unsigned int capacity;\
}\


/**
 * reserve a chunck of data
 * @param vec the dynamic array
 * @param nb_element the number of element you want allocate
 * @param size_type the size of types you wants for your dynamic array
 */
#define VecReserve(vec,nb_element,type)\
{   \
    vec.size = nb_element;\
    vec.capacity = vec.size + 5;\
    vec.size_type = sizeof(type);\
    vec.full_data = malloc(vec.capacity * vec.size_type);\
}\

#define VecInsert(vec, elements)\
{\
    for(unsigned int i = 0; i < vec.size; ++i)\
    {\
        vec.full_data[i] = elements[i];\
    }\
}\

/**
 * push an element at the end of the array
 * @param vec the dynamic array
 * @param element the element to be pushed
 */
#define VecPush_back(vec, element)\
{\
    if(vec.size >= vec.capacity)\
    {\
        vec.capacity = vec.size + 5;\
        vec.full_data = realloc(vec.full_data, vec.capacity * vec.size_type);\
    }\
    vec.full_data[vec.size] = element;\
    vec.size += 1;\
}\

/**
 * get the pointer to the array
 * @param vec the dynamic array
 * @return the pointer to the array
 */
#define VecData(vec, relevent_data)\
{\
    memcpy(relevent_data, vec.full_data, vec.size);\
    \
}\

/**
 * free the memory taken by the array
 * @param vec the dynamic array
 */
#define VecClean(vec)\
{\
    free(vec.full_data);\
}\

#endif
