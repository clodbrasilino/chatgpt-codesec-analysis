#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef enum {
    TYPE_INT,
    TYPE_TUPLE
} ElementType;

typedef struct Element {
    ElementType type;
    union {
        int int_value;
        struct Element **tuple_elements;
    } data;
    int tuple_size;
} Element;

Element *create_int_element(int value) {
    Element *elem = (Element *)malloc(sizeof(Element));
    if (!elem) {
        return NULL;
    }
    elem->type = TYPE_INT;
    elem->data.int_value = value;
    elem->tuple_size = 0;
    return elem;
}

Element *create_tuple_element(Element **elements, int size) {
    Element *elem = (Element *)malloc(sizeof(Element));
    if (!elem) {
        return NULL;
    }
    elem->type = TYPE_TUPLE;
    elem->data.tuple_elements = elements;
    elem->tuple_size = size;
    return elem;
}

void free_element(Element *elem) {
    if (!elem) {
        return;
    }
    if (elem->type == TYPE_TUPLE && elem->data.tuple_elements) {
        for (int i = 0; i < elem->tuple_size; i++) {
            free_element(elem->data.tuple_elements[i]);
        }
        free(elem->data.tuple_elements);
    }
    free(elem);
}

int *extract_even_elements(Element *root, int *count) {
    int *result = NULL;
    *count = 0;
    
    if (!root) {
        return NULL;
    }
    
    if (root->type == TYPE_INT) {
        if (root->data.int_value % 2 == 0) {
            result = (int *)malloc(sizeof(int));
            if (result) {
                result[0] = root->data.int_value;
                *count = 1;
            }
        }
        return result;
    }
    
    if (root->type == TYPE_TUPLE) {
        for (int i = 0; i < root->tuple_size; i++) {
            int sub_count = 0;
            int *sub_result = extract_even_elements(root->data.tuple_elements[i], &sub_count);
            if (sub_result && sub_count > 0) {
                int *new_result = (int *)realloc(result, (*count + sub_count) * sizeof(int));
                if (new_result) {
                    result = new_result;
                    for (int j = 0; j < sub_count; j++) {
                        result[*count + j] = sub_result[j];
                    }
                    *count += sub_count;
                }
                free(sub_result);
            }
        }
    }
    
    return result;
}

int main() {
    Element **nested_tuple = (Element **)malloc(3 * sizeof(Element *));
    if (!nested_tuple) {
        return 1;
    }
    nested_tuple[0] = create_int_element(1);
    nested_tuple[1] = create_int_element(2);
    nested_tuple[2] = create_int_element(3);
    Element *tuple1 = create_tuple_element(nested_tuple, 3);
    
    Element **nested_tuple2 = (Element **)malloc(3 * sizeof(Element *));
    if (!nested_tuple2) {
        free_element(tuple1);
        return 1;
    }
    nested_tuple2[0] = create_int_element(4);
    nested_tuple2[1] = create_int_element(5);
    nested_tuple2[2] = create_int_element(6);
    Element *tuple2 = create_tuple_element(nested_tuple2, 3);
    
    Element **top_level = (Element **)malloc(3 * sizeof(Element *));
    if (!top_level) {
        free_element(tuple1);
        free_element(tuple2);
        return 1;
    }
    top_level[0] = tuple1;
    top_level[1] = create_int_element(7);
    top_level[2] = tuple2;
    Element *root = create_tuple_element(top_level, 3);
    
    int count = 0;
    int *even_elements = extract_even_elements(root, &count);
    
    for (int i = 0; i < count; i++) {
        printf("%d ", even_elements[i]);
    }
    if (count > 0) {
        printf("\n");
    }
    
    free(even_elements);
    free_element(root);
    
    return 0;
}