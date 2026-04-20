#include <stddef.h>

typedef struct List List; // there is a type called List, defined by struct List


List* init_list(size_t capacity);

void* get_from_list(List* l, size_t index);

int add_to_list(List* l, void* value); //adds to last
int insert_to_index_in_list(List* l, void* value, size_t index);

int remove_from_list(List* l, void* value, size_t s);
int destroy_list(List* l);

size_t size_of_list(List* l);
