#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_CHAR
} DataType;

typedef struct {
    DataType type;
    union {
        int int_val;
        float float_val;
        char char_val;
    } value;
} TupleElement;

typedef struct {
    TupleElement *elements;
    size_t size;
    size_t capacity;
} Tuple;

Tuple tuple_create(size_t capacity) {
    Tuple t;
    t.elements = (TupleElement *)malloc(capacity * sizeof(TupleElement));
    if (t.elements == NULL) {
        t.size = 0;
        t.capacity = 0;
        return t;
    }
    t.size = 0;
    t.capacity = capacity;
    return t;
}

int tuple_append(Tuple *t, TupleElement element) {
    if (t == NULL || t->elements == NULL) {
        return -1;
    }
    if (t->size >= t->capacity) {
        size_t new_capacity = t->capacity == 0 ? 1 : t->capacity * 2;
        TupleElement *new_elements = (TupleElement *)realloc(t->elements, new_capacity * sizeof(TupleElement));
        if (new_elements == NULL) {
            return -1;
        }
        t->elements = new_elements;
        t->capacity = new_capacity;
    }
    t->elements[t->size] = element;
    t->size++;
    return 0;
}

Tuple tuple_remove_type(Tuple *t, DataType type_to_remove) {
    Tuple result;
    if (t == NULL || t->elements == NULL) {
        result.elements = NULL;
        result.size = 0;
        result.capacity = 0;
        return result;
    }
    result = tuple_create(t->size);
    if (result.elements == NULL) {
        return result;
    }
    for (size_t i = 0; i < t->size; i++) {
        if (t->elements[i].type != type_to_remove) {
            if (tuple_append(&result, t->elements[i]) != 0) {
                free(result.elements);
                result.elements = NULL;
                result.size = 0;
                result.capacity = 0;
                return result;
            }
        }
    }
    return result;
}

void tuple_destroy(Tuple *t) {
    if (t != NULL) {
        free(t->elements);
        t->elements = NULL;
        t->size = 0;
        t->capacity = 0;
    }
}

void tuple_print(Tuple *t) {
    if (t == NULL || t->elements == NULL) {
        printf("Invalid tuple\n");
        return;
    }
    printf("(");
    for (size_t i = 0; i < t->size; i++) {
        switch (t->elements[i].type) {
            case TYPE_INT:
                printf("%d", t->elements[i].value.int_val);
                break;
            case TYPE_FLOAT:
                printf("%f", t->elements[i].value.float_val);
                break;
            case TYPE_CHAR:
                printf("'%c'", t->elements[i].value.char_val);
                break;
        }
        if (i < t->size - 1) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void) {
    Tuple t = tuple_create(4);
    if (t.elements == NULL) {
        return EXIT_FAILURE;
    }

    TupleElement e1 = {TYPE_INT, .value.int_val = 10};
    TupleElement e2 = {TYPE_FLOAT, .value.float_val = 3.14f};
    TupleElement e3 = {TYPE_CHAR, .value.char_val = 'X'};
    TupleElement e4 = {TYPE_INT, .value.int_val = 20};

    if (tuple_append(&t, e1) != 0 || tuple_append(&t, e2) != 0 ||
        tuple_append(&t, e3) != 0 || tuple_append(&t, e4) != 0) {
        tuple_destroy(&t);
        return EXIT_FAILURE;
    }

    printf("Original: ");
    tuple_print(&t);

    Tuple filtered = tuple_remove_type(&t, TYPE_INT);
    if (filtered.elements == NULL) {
        tuple_destroy(&t);
        return EXIT_FAILURE;
    }

    printf("Filtered: ");
    tuple_print(&filtered);

    tuple_destroy(&t);
    tuple_destroy(&filtered);

    return EXIT_SUCCESS;
}