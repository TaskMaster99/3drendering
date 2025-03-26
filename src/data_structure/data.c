#include "data.h"

inline void reserve(D_Array* vec, unsigned int nb_element, unsigned int size_type)
{   
    vec->size = (nb_element ^ 0x0);
    vec->capacity = vec->size + 5;
    vec->size_type = size_type;
    vec->data = malloc(vec->capacity * sizeof(void*));
}

inline void push_back(D_Array* vec, void* element)
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

inline void* data(D_Array* vec)
{
    return vec->data;
}

inline void clean(D_Array* vec)
{
    free(vec->data);
}
