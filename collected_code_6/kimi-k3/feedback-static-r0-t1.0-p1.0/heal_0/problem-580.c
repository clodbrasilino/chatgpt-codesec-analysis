#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    TYPE_INT,
    TYPE_TUPLE
} ElementType;

typedef struct Element {
    ElementType type;
    union {
        int value;
        struct {
            struct Element *elements;
            size_t count;
            size_t capacity;
        } tuple;
    } data;
} Element;

typedef struct {
    int *data;
    size_t count;
    size_t capacity;
} IntArray;

Element *create_int_element(int value) {
    Element *elem = (Element *)malloc(sizeof(Element));
    if (elem == NULL) {
        return NULL;
    }
    elem->type = TYPE_INT;
    elem->data.value = value;
    return elem;
}

Element *create_tuple_element(void) {
    Element *elem = (Element *)malloc(sizeof(Element));
    if (elem == NULL) {
        return NULL;
    }
    elem->type = TYPE_TUPLE;
    elem->data.tuple.elements = NULL;
    elem->data.tuple.count = 0;
    elem->data.tuple.capacity = 0;
    return elem;
}

int add_element_to_tuple(Element *tuple, Element *element) {
    if (tuple == NULL || element == NULL || tuple->type != TYPE_TUPLE) {
        return -1;
    }

    if (tuple->data.tuple.count >= tuple->data.tuple.capacity) {
        size_t new_capacity = (tuple->data.tuple.capacity == 0) ? 4 : tuple->data.tuple.capacity * 2;
        Element *new_elements = (Element *)realloc(tuple->data.tuple.elements, new_capacity * sizeof(Element));
        if (new_elements == NULL) {
            return -1;
        }
        tuple->data.tuple.elements = new_elements;
        tuple->data.tuple.capacity = new_capacity;
    }

    tuple->data.tuple.elements[tuple->data.tuple.count] = *element;
    tuple->data.tuple.count++;
    free(element);
    return 0;
}

void free_element(Element *elem) {
    if (elem == NULL) {
        return;
    }
    if (elem->type == TYPE_TUPLE) {
        for (size_t i = 0; i < elem->data.tuple.count; i++) {
            free_element(&elem->data.tuple.elements[i]);
        }
        free(elem->data.tuple.elements);
    }
}

int init_int_array(IntArray *arr) {
    if (arr == NULL) {
        return -1;
    }
    arr->data = NULL;
    arr->count = 0;
    arr->capacity = 0;
    return 0;
}

int add_to_int_array(IntArray *arr, int value) {
    if (arr == NULL) {
        return -1;
    }
    if (arr->count >= arr->capacity) {
        size_t new_capacity = (arr->capacity == 0) ? 4 : arr->capacity * 2;
        int *new_data = (int *)realloc(arr->data, new_capacity * sizeof(int));
        if (new_data == NULL) {
            return -1;
        }
        arr->data = new_data;
        arr->capacity = new_capacity;
    }
    arr->data[arr->count] = value;
    arr->count++;
    return 0;
}

void free_int_array(IntArray *arr) {
    if (arr == NULL) {
        return;
    }
    free(arr->data);
    arr->data = NULL;
    arr->count = 0;
    arr->capacity = 0;
}

int extract_even_elements(const Element *elem, IntArray *result) {
    if (elem == NULL || result == NULL) {
        return -1;
    }

    if (elem->type == TYPE_INT) {
        if (elem->data.value % 2 == 0) {
            if (add_to_int_array(result, elem->data.value) != 0) {
                return -1;
            }
        }
    } else if (elem->type == TYPE_TUPLE) {
        for (size_t i = 0; i < elem->data.tuple.count; i++) {
            if (extract_even_elements(&elem->data.tuple.elements[i], result) != 0) {
                return -1;
            }
        }
    }
    return 0;
}

int main(void) {
    Element *root = create_tuple_element();
    if (root == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    Element *e1 = create_int_element(1);
    Element *e2 = create_int_element(2);
    Element *e3 = create_int_element(3);
    Element *e4 = create_int_element(4);
    Element *nested = create_tuple_element();
    Element *e5 = create_int_element(5);
    Element *e6 = create_int_element(6);
    Element *e7 = create_int_element(8);

    if (e1 == NULL || e2 == NULL || e3 == NULL || e4 == NULL || 
        nested == NULL || e5 == NULL || e6 == NULL || e7 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free_element(root);
        free(root);
        return EXIT_FAILURE;
    }

    if (add_element_to_tuple(root, e1) != 0 ||
        add_element_to_tuple(root, e2) != 0 ||
        add_element_to_tuple(root, e3) != 0 ||
        add_element_to_tuple(root, e4) != 0) {
        fprintf(stderr, "Failed to add elements\n");
        free_element(root);
        free(root);
        return EXIT_FAILURE;
    }

    if (add_element_to_tuple(nested, e5) != 0 ||
        add_element_to_tuple(nested, e6) != 0 ||
        add_element_to_tuple(nested, e7) != 0) {
        fprintf(stderr, "Failed to add elements to nested tuple\n");
        free_element(nested);
        free(nested);
        free_element(root);
        free(root);
        return EXIT_FAILURE;
    }

    if (add_element_to_tuple(root, nested) != 0) {
        fprintf(stderr, "Failed to add nested tuple\n");
        free_element(nested);
        free(nested);
        free_element(root);
        free(root);
        return EXIT_FAILURE;
    }

    IntArray result;
    if (init_int_array(&result) != 0) {
        fprintf(stderr, "Failed to initialize result array\n");
        free_element(root);
        free(root);
        return EXIT_FAILURE;
    }

    if (extract_even_elements(root, &result) != 0) {
        fprintf(stderr, "Failed to extract even elements\n");
        free_int_array(&result);
        free_element(root);
        free(root);
        return EXIT_FAILURE;
    }

    printf("Even elements: ");
    for (size_t i = 0; i < result.count; i++) {
        printf("%d ", result.data[i]);
    }
    printf("\n");

    free_int_array(&result);
    free_element(root);
    free(root);

    return EXIT_SUCCESS;
}