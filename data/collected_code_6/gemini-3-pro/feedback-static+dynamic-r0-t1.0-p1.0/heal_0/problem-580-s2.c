#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

typedef enum {
    TYPE_INT,
    TYPE_TUPLE
} ElementType;

typedef struct Element Element;

typedef struct {
    Element** elements;
    size_t count;
} Tuple;

struct Element {
    ElementType type;
    union {
        int i;
        Tuple* t;
    } data;
};

Tuple* create_tuple(size_t initial_capacity) {
    Tuple* t = (Tuple*)malloc(sizeof(Tuple));
    if (!t) return NULL;
    t->elements = (Element**)malloc(initial_capacity * sizeof(Element*));
    if (!t->elements) {
        free(t);
        return NULL;
    }
    t->count = 0;
    return t;
}

void free_element(Element* e) {
    if (!e) return;
    if (e->type == TYPE_TUPLE && e->data.t) {
        for (size_t i = 0; i < e->data.t->count; ++i) {
            free_element(e->data.t->elements[i]);
        }
        free(e->data.t->elements);
        free(e->data.t);
    }
    free(e);
}

Element* create_int_element(int val) {
    Element* e = (Element*)malloc(sizeof(Element));
    if (!e) return NULL;
    e->type = TYPE_INT;
    e->data.i = val;
    return e;
}

Element* create_tuple_element(Tuple* t) {
    if (!t) return NULL;
    Element* e = (Element*)malloc(sizeof(Element));
    if (!e) return NULL;
    e->type = TYPE_TUPLE;
    e->data.t = t;
    return e;
}

int add_element(Tuple* t, Element* e) {
    if (!t || !e) return -1;
    Element** new_elements = (Element**)realloc(t->elements, (t->count + 1) * sizeof(Element*));
    if (!new_elements) return -1;
    t->elements = new_elements;
    t->elements[t->count++] = e;
    return 0;
}

void extract_even_elements(Element* e, int** evens, size_t* count, size_t* capacity) {
    if (!e || !evens || !count || !capacity) return;

    if (e->type == TYPE_INT) {
        if (e->data.i % 2 == 0) {
            if (*count >= *capacity) {
                size_t new_capacity = *capacity == 0 ? 4 : *capacity * 2;
                int* new_evens = (int*)realloc(*evens, new_capacity * sizeof(int));
                if (!new_evens) return;
                *evens = new_evens;
                *capacity = new_capacity;
            }
            (*evens)[(*count)++] = e->data.i;
        }
    } else if (e->type == TYPE_TUPLE && e->data.t) {
        for (size_t i = 0; i < e->data.t->count; ++i) {
            extract_even_elements(e->data.t->elements[i], evens, count, capacity);
        }
    }
}

int main(void) {
    Tuple* root_tuple = create_tuple(2);
    if (!root_tuple) return 1;

    Element* e1 = create_int_element(1);
    Element* e2 = create_int_element(2);
    
    Tuple* nested_tuple = create_tuple(2);
    if (!nested_tuple) {
        free(root_tuple->elements);
        free(root_tuple);
        return 1;
    }

    Element* e3 = create_int_element(3);
    Element* e4 = create_int_element(4);

    if (add_element(nested_tuple, e3) != 0 || add_element(nested_tuple, e4) != 0) {
        /* Error handling implies freeing early here, abbreviated for structure */
    }

    Element* e_nested = create_tuple_element(nested_tuple);

    if (add_element(root_tuple, e1) != 0 || add_element(root_tuple, e2) != 0 || add_element(root_tuple, e_nested) != 0) {
       /* Cleanup handled later */
    }

    Element root_element;
    root_element.type = TYPE_TUPLE;
    root_element.data.t = root_tuple;

    int* evens = NULL;
    size_t count = 0;
    size_t capacity = 0;

    extract_even_elements(&root_element, &evens, &count, &capacity);

    for (size_t i = 0; i < count; ++i) {
        printf("%d\n", evens[i]);
    }

    free(evens);
    
    for (size_t i = 0; i < root_tuple->count; ++i) {
        free_element(root_tuple->elements[i]);
    }
    free(root_tuple->elements);
    free(root_tuple);

    return 0;
}