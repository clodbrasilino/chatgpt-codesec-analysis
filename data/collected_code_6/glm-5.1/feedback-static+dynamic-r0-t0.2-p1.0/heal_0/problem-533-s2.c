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
    } data;
} TupleElement;

typedef struct {
    TupleElement *elements;
    size_t size;
    size_t capacity;
} Tuple;

Tuple tuple_create(size_t capacity) {
    Tuple t;
    t.capacity = capacity > 0 ? capacity : 1;
    t.size = 0;
    t.elements = (TupleElement *)malloc(t.capacity * sizeof(TupleElement));
    if (t.elements == NULL) {
        exit(EXIT_FAILURE);
    }
    return t;
}

void tuple_add_int(Tuple *t, int val) {
    if (t->size >= t->capacity) {
        t->capacity *= 2;
        TupleElement *new_elements = (TupleElement *)realloc(t->elements, t->capacity * sizeof(TupleElement));
        if (new_elements == NULL) {
            free(t->elements);
            exit(EXIT_FAILURE);
        }
        t->elements = new_elements;
    }
    t->elements[t->size].type = TYPE_INT;
    t->elements[t->size].data.int_val = val;
    t->size++;
}

void tuple_add_float(Tuple *t, float val) {
    if (t->size >= t->capacity) {
        t->capacity *= 2;
        TupleElement *new_elements = (TupleElement *)realloc(t->elements, t->capacity * sizeof(TupleElement));
        if (new_elements == NULL) {
            free(t->elements);
            exit(EXIT_FAILURE);
        }
        t->elements = new_elements;
    }
    t->elements[t->size].type = TYPE_FLOAT;
    t->elements[t->size].data.float_val = val;
    t->size++;
}

void tuple_add_char(Tuple *t, char val) {
    if (t->size >= t->capacity) {
        t->capacity *= 2;
        TupleElement *new_elements = (TupleElement *)realloc(t->elements, t->capacity * sizeof(TupleElement));
        if (new_elements == NULL) {
            free(t->elements);
            exit(EXIT_FAILURE);
        }
        t->elements = new_elements;
    }
    t->elements[t->size].type = TYPE_CHAR;
    t->elements[t->size].data.char_val = val;
    t->size++;
}

Tuple tuple_remove_type(const Tuple *t, DataType type_to_remove) {
    Tuple result = tuple_create(t->size > 0 ? t->size : 1);
    for (size_t i = 0; i < t->size; i++) {
        if (t->elements[i].type != type_to_remove) {
            if (result.size >= result.capacity) {
                result.capacity *= 2;
                TupleElement *new_elements = (TupleElement *)realloc(result.elements, result.capacity * sizeof(TupleElement));
                if (new_elements == NULL) {
                    free(result.elements);
                    exit(EXIT_FAILURE);
                }
                result.elements = new_elements;
            }
            result.elements[result.size] = t->elements[i];
            result.size++;
        }
    }
    return result;
}

void tuple_free(Tuple *t) {
    free(t->elements);
    t->elements = NULL;
    t->size = 0;
    t->capacity = 0;
}

void tuple_print(const Tuple *t) {
    printf("(");
    for (size_t i = 0; i < t->size; i++) {
        switch (t->elements[i].type) {
            case TYPE_INT:
                printf("%d", t->elements[i].data.int_val);
                break;
            case TYPE_FLOAT:
                printf("%f", t->elements[i].data.float_val);
                break;
            case TYPE_CHAR:
                printf("'%c'", t->elements[i].data.char_val);
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
    tuple_add_int(&t, 10);
    tuple_add_float(&t, 3.14f);
    tuple_add_char(&t, 'A');
    tuple_add_int(&t, 20);

    printf("Original: ");
    tuple_print(&t);

    Tuple t_no_int = tuple_remove_type(&t, TYPE_INT);
    printf("Without INT: ");
    tuple_print(&t_no_int);

    Tuple t_no_float = tuple_remove_type(&t, TYPE_FLOAT);
    printf("Without FLOAT: ");
    tuple_print(&t_no_float);

    Tuple t_no_char = tuple_remove_type(&t, TYPE_CHAR);
    printf("Without CHAR: ");
    tuple_print(&t_no_char);

    tuple_free(&t);
    tuple_free(&t_no_int);
    tuple_free(&t_no_float);
    tuple_free(&t_no_char);

    return 0;
}