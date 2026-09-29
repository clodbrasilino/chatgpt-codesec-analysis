#include <stdio.h>
#include <stddef.h>

typedef enum {
    ELEMENT_INT,
    ELEMENT_LIST,
    ELEMENT_TUPLE
} ElementType;

typedef struct Element {
    ElementType type;
    struct Element* elements;
    size_t count;
} Element;

size_t count_lists_in_tuple(const Element* tuple);

size_t count_lists_in_tuple(const Element* tuple) {
    size_t list_count = 0;
    size_t i;

    if (tuple == NULL) {
        return 0;
    }

    if (tuple->type != ELEMENT_TUPLE) {
        return 0;
    }

    if (tuple->elements == NULL && tuple->count > 0) {
        return 0;
    }

    for (i = 0; i < tuple->count; i++) {
        if (tuple->elements[i].type == ELEMENT_LIST) {
            list_count++;
        }
    }

    return list_count;
}

int main(void) {
    Element list1 = { ELEMENT_LIST, NULL, 0 };
    Element list2 = { ELEMENT_LIST, NULL, 0 };
    Element integer1 = { ELEMENT_INT, NULL, 0 };
    
    Element tuple_elements[3] = { list1, integer1, list2 };
    
    Element my_tuple = { ELEMENT_TUPLE, tuple_elements, 3 };
    
    size_t result = 0;
    
    result = count_lists_in_tuple(&my_tuple);
    
    printf("%zu\n", result);
    
    return 0;
}