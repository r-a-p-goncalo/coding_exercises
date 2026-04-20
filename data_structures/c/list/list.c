#include "list.h"
#include <stdlib.h>

struct List {
    size_t s;
    size_t capacity;
    void** values; //not void*, we want the compiler to know this is a pointer to pointers
};

List* init_list(size_t capacity){

    List* l = malloc(sizeof(List));

    //if l was not properly instatiated, if it is null, return null
    if (!l) return NULL;

    l->s = 0;
    l->capacity = capacity;
    l->values = malloc(sizeof(void*) * capacity); 

    if (!l->values) {
        free(l);
        return NULL;
    }

    return l;

}

void* get_from_list(List* l, size_t index){

    if (l == NULL || index >= l->s) {
        return NULL;
    }

    return l->values[index];
}

int add_to_list(List* l, void* value){

    if (l->s >= l->capacity){
        return 1;

    }

    l->values[l->s] = value;
    l->s = l->s + 1;

    return 0;

}


int destroy_list(List* l){

    free(l->values);
    free(l);

    return 0;

}