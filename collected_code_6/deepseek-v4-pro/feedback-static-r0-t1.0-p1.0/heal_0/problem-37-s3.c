#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    INT_TYPE,
    STR_TYPE
} Type;

typedef struct {
    Type type;
    union {
        int int_val;
        char *str_val;
    } data;
} Element;

int compare_elements(const void *a, const void *b) {
    const Element *elem_a = (const Element *)a;
    const Element *elem_b = (const Element *)b;
    
    if (elem_a->type != elem_b->type) {
        return elem_a->type - elem_b->type;
    }
    
    if (elem_a->type == INT_TYPE) {
        return elem_a->data.int_val - elem_b->data.int_val;
    }
    
    return strcmp(elem_a->data.str_val, elem_b->data.str_val);
}

void sort_mixed_list(Element *list, size_t size) {
    if (list == NULL || size == 0) {
        return;
    }
    qsort(list, size, sizeof(Element), compare_elements);
}

void free_mixed_list(Element *list, size_t size) {
    if (list == NULL) {
        return;
    }
    for (size_t i = 0; i < size; i++) {
        if (list[i].type == STR_TYPE) {
            free(list[i].data.str_val);
        }
    }
    free(list);
}

Element *create_mixed_list(size_t size) {
    Element *list = (Element *)calloc(size, sizeof(Element));
    return list;
}

int main(void) {
    size_t size = 5;
    Element *list = create_mixed_list(size);
    
    if (list == NULL) {
        return EXIT_FAILURE;
    }
    
    list[0].type = INT_TYPE;
    list[0].data.int_val = 42;
    
    list[1].type = STR_TYPE;
    list[1].data.str_val = strdup("banana");
    if (list[1].data.str_val == NULL) {
        free_mixed_list(list, size);
        return EXIT_FAILURE;
    }
    
    list[2].type = INT_TYPE;
    list[2].data.int_val = 7;
    
    list[3].type = STR_TYPE;
    list[3].data.str_val = strdup("apple");
    if (list[3].data.str_val == NULL) {
        free_mixed_list(list, size);
        return EXIT_FAILURE;
    }
    
    list[4].type = INT_TYPE;
    list[4].data.int_val = 15;
    
    sort_mixed_list(list, size);
    
    for (size_t i = 0; i < size; i++) {
        if (list[i].type == INT_TYPE) {
            printf("%d ", list[i].data.int_val);
        } else {
            printf("%s ", list[i].data.str_val);
        }
    }
    printf("\n");
    
    free_mixed_list(list, size);
    
    return EXIT_SUCCESS;
}