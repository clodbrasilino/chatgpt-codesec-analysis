#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_CHAR,
    TYPE_TUPLE
} ElementType;

typedef struct ListElement {
    ElementType type;
    union {
        int int_val;
        float float_val;
        char char_val;
        struct ListElement** tuple_elements;
    } data;
    size_t tuple_size;
    struct ListElement* next;
} ListElement;

ListElement* create_int_element(int val) {
    ListElement* elem = (ListElement*)malloc(sizeof(ListElement));
    if (!elem) {
        exit(EXIT_FAILURE);
    }
    elem->type = TYPE_INT;
    elem->data.int_val = val;
    elem->tuple_size = 0;
    elem->next = NULL;
    return elem;
}

ListElement* create_tuple_element(ListElement** elements, size_t size) {
    ListElement* elem = (ListElement*)malloc(sizeof(ListElement));
    if (!elem) {
        exit(EXIT_FAILURE);
    }
    elem->type = TYPE_TUPLE;
    elem->data.tuple_elements = elements;
    elem->tuple_size = size;
    elem->next = NULL;
    return elem;
}

void free_list(ListElement* head) {
    ListElement* current = head;
    while (current != NULL) {
        ListElement* next = current->next;
        if (current->type == TYPE_TUPLE) {
            for (size_t i = 0; i < current->tuple_size; ++i) {
                free_list(current->data.tuple_elements[i]);
            }
            free(current->data.tuple_elements);
        }
        free(current);
        current = next;
    }
}

size_t count_until_tuple(const ListElement* head) {
    size_t count = 0;
    const ListElement* current = head;
    while (current != NULL) {
        if (current->type == TYPE_TUPLE) {
            break;
        }
        count++;
        current = current->next;
    }
    return count;
}

int main(void) {
    ListElement* elem1 = create_int_element(10);
    ListElement* elem2 = create_int_element(20);
    ListElement* elem3 = create_int_element(30);

    ListElement** tuple_contents = (ListElement**)malloc(2 * sizeof(ListElement*));
    if (!tuple_contents) {
        free(elem1);
        free(elem2);
        free(elem3);
        exit(EXIT_FAILURE);
    }
    tuple_contents[0] = create_int_element(40);
    tuple_contents[1] = create_int_element(50);
    
    ListElement* tuple_elem = create_tuple_element(tuple_contents, 2);
    ListElement* elem5 = create_int_element(60);

    elem1->next = elem2;
    elem2->next = elem3;
    elem3->next = tuple_elem;
    tuple_elem->next = elem5;

    size_t count = count_until_tuple(elem1);
    printf("%zu\n", count);

    free_list(elem1);

    return 0;
}