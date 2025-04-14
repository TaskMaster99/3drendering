#ifndef LINKED_LIST
#define LINKED_LIST

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * node
 * @param value value of the node
 * @param next pointer to the next node
 */
#define Node(__TYPE__) \
struct node_##__TYPE__\
{\
    __TYPE__ value;\
    struct node_##__TYPE__* next;\
}\

/**
 * create a node
 * @param element element of the node created
 * @param src the empty node
 */
#define NoCreate_node(src, element)\
{\
    src.value = element;\
    src.next = NULL;\
}\
/**
 * add a node to a node
 * @param element element of the node created
 * @param src source node
 */
#define NoAdd_element(src,  element)\
{\
    src.next = (node*)malloc(sizeof(node));\
    create_node(element, src.next);\
}\
/**
 * remove a node to a node
 * @param element element of the node to delete
 * @param src source node
 */
#define NoRemove_element(src,  element_delete)\
{\
    tmp = NULL;\
    bg = src;\
    pred = NULL;\
    \
    while (src != NULL) {\
        if(src.value == element_delete)\
        {\
            tmp = src;\
            if(pred)\
            {\
                pred.next = src.next;\
                src = bg;\
                free(tmp);\
            }\
            else\
                {   \                 
                    *src = *src.next;\
                }    \       
            break;\
        }\
        pred = src;\
        src = src.next;\
    }\
}\
/**
 * insert a node after it
 * @param element_at where to insert an element
 * @param element_insert element to insert
 * @param src source node
 */
#define NoInsert_element(src,  element_at, element_insert)\
{\
    tmp = NULL;\
    bg = src;\
    \
    while (src != NULL) {\
        if(src.value == element_at)\
        {\
            tmp = src.next;\
            add_element(src.next, element_insert);\
            src.next = tmp;\
            break;\
        }\
        src = src.next;\
    }\
    src = bg;\
}\

/**
 * free the memory
 * @param src source node
 */
#define NoClean(src)\
{\
    tmp = src.next;\
    tmp0 = NULL;\
    while (tmp != NULL) {\
        tmp0 = tmp.next;\
        free(tmp);\
        tmp = tmp0;\
    }\
}\

#endif