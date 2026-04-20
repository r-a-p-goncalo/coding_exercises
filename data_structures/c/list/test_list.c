#include "list.h"


void test_correct_gettin_values_from_list(){

    printf("Testing that getting values from general type list is correctly implemented\n");

    List* list = init_list(3);

    if (!list) {
        printf("FAIL\n");
        return;
    }

    int a = 10, b = 20, c = 30;

    add_to_list(list, &a);
    add_to_list(list, &b);
    add_to_list(list, &c);

    int gotten_a = *(int*)get_from_list(list, 0);
    int gotten_a_sec = *(int*)get_from_list(list, 0);

    int gotten_b = *(int*)get_from_list(list, 1);
    
    int gotten_c = *(int*)get_from_list(list, 2);

    printf("%d == %d == %d\n", a, gotten_a, gotten_a_sec);
    printf("%d == %d\n", b, gotten_b);
    printf("%d == %d\n", c, gotten_c);

}

void test_general_type_list(){

    printf("Testing the implemented general type list...\n\n");

    test_correct_gettin_values_from_list();

}


void test_lists(){

    printf("Testing the implemented lists datatypes...\n\n");
    test_general_type_list();
    
}