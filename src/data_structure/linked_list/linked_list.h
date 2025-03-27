#ifndef LINKED_LIST
#define LINKED_LIST

#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char* value;
    struct node* next;
} __attribute__((aligned(64))) node;


void create_node(char* element, node* src)
{
    src->value = element;
    src->next = NULL;
}

void add_element(node* src, char* element)
{
    src->next = (node*)malloc(sizeof(node));
    create_node(element, src->next);
}

void remove_element(node* src, char* element_delete)
{
    node* tmp = NULL;
    node* bg = src;
    node* pred = NULL;

    while (src != NULL) {
        if(src->value == element_delete)
        {
            tmp = src;
            if(pred)
            {
                pred->next = src->next;
                src = bg;
                free(tmp);
            }
            else
                {                    
                    *src = *src->next;
                }           
            break;
        }
        pred = src;
        src = src->next;
    }
}

void insert_element(node* src, char* element_at,char* element_insert)
{
    node* tmp = NULL;
    node* bg = src;

    while (src != NULL) {
        if(src->value == element_at)
        {
            tmp = src->next;
            add_element(src->next, element_insert);
            src->next = tmp;
            break;
        }
        src = src->next;
    }
    src = bg;
}

void display_list(node* src)
{
    node* bg = src;
    while (src != NULL) {
        printf("value : %d.\n",(int)(*src->value));        
        src = src->next;
    }
    src = bg;
    printf("\n");
}

void free_list(node* src)
{
    node* tmp = src->next;
    node* tmp0 = NULL;
    while (tmp != NULL) {
        tmp0 = tmp->next;
        free(tmp);
        tmp = tmp0;
    }
}

#endif