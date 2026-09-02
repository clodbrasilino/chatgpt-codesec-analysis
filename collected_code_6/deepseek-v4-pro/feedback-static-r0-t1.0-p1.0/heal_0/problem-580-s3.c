#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum {
    TYPE_INT,
    TYPE_TUPLE
} ElementType;

typedef struct Element {
    ElementType type;
    union {
        int int_val;
        struct Element **tuple;
    } data;
    size_t tuple_size;
} Element;

typedef struct {
    int *values;
    size_t count;
    size_t capacity;
} Result;

bool is_even(int value) {
    return value % 2 == 0;
}

void init_result(Result *result) {
    if (result == NULL) {
        return;
    }
    result->values = NULL;
    result->count = 0;
    result->capacity = 0;
}

bool add_value(Result *result, int value) {
    if (result == NULL) {
        return false;
    }
    if (result->count >= result->capacity) {
        size_t new_capacity = result->capacity == 0 ? 8 : result->capacity * 2;
        int *new_values = (int *)realloc(result->values, new_capacity * sizeof(int));
        if (new_values == NULL) {
            return false;
        }
        result->values = new_values;
        result->capacity = new_capacity;
    }
    result->values[result->count++] = value;
    return true;
}

void extract_even_from_element(const Element *element, Result *result) {
    if (element == NULL || result == NULL) {
        return;
    }
    
    if (element->type == TYPE_INT) {
        if (is_even(element->data.int_val)) {
            add_value(result, element->data.int_val);
        }
    } else if (element->type == TYPE_TUPLE) {
        if (element->data.tuple == NULL) {
            return;
        }
        for (size_t i = 0; i < element->tuple_size; i++) {
            if (element->data.tuple[i] != NULL) {
                extract_even_from_element(element->data.tuple[i], result);
            }
        }
    }
}

Result extract_even_elements(const Element *root) {
    Result result;
    init_result(&result);
    
    if (root == NULL) {
        return result;
    }
    
    extract_even_from_element(root, &result);
    return result;
}

Element *create_int_element(int value) {
    Element *element = (Element *)malloc(sizeof(Element));
    if (element == NULL) {
        return NULL;
    }
    element->type = TYPE_INT;
    element->data.int_val = value;
    element->tuple_size = 0;
    return element;
}

Element *create_tuple_element(Element **elements, size_t count) {
    Element *element = (Element *)malloc(sizeof(Element));
    if (element == NULL) {
        return NULL;
    }
    element->type = TYPE_TUPLE;
    element->tuple_size = count;
    
    if (count > 0) {
        element->data.tuple = (Element **)malloc(count * sizeof(Element *));
        if (element->data.tuple == NULL) {
            free(element);
            return NULL;
        }
        for (size_t i = 0; i < count; i++) {
            element->data.tuple[i] = elements[i];
        }
    } else {
        element->data.tuple = NULL;
    }
    return element;
}

void free_element(Element *element) {
    if (element == NULL) {
        return;
    }
    if (element->type == TYPE_TUPLE) {
        if (element->data.tuple != NULL) {
            for (size_t i = 0; i < element->tuple_size; i++) {
                free_element(element->data.tuple[i]);
                element->data.tuple[i] = NULL;
            }
            free(element->data.tuple);
            element->data.tuple = NULL;
        }
    }
    free(element);
}

int main(void) {
    Element *int1 = create_int_element(2);
    Element *int2 = create_int_element(3);
    Element *int3 = create_int_element(4);
    Element *int4 = create_int_element(5);
    Element *int5 = create_int_element(6);
    Element *int6 = create_int_element(7);
    Element *int7 = create_int_element(8);
    Element *int8 = create_int_element(9);
    Element *int9 = create_int_element(10);
    
    Element *inner_tuple_elements[] = {int3, int4, int5};
    Element *inner_tuple = create_tuple_element(inner_tuple_elements, 3);
    
    Element *outer_tuple_elements[] = {int1, int2, inner_tuple, int6, int7, int8, int9};
    Element *root = create_tuple_element(outer_tuple_elements, 7);
    
    Result result = extract_even_elements(root);
    
    for (size_t i = 0; i < result.count; i++) {
        printf("%d ", result.values[i]);
    }
    printf("\n");
    
    free(result.values);
    free_element(root);
    
    return 0;
}