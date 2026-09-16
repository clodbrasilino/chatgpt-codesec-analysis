#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_CHAR,
    TYPE_PTR
} DataType;

typedef struct {
    DataType type;
    union {
        int int_val;
        float float_val;
        /* Possible weaknesses found:
         *  union member 'Anonymous0::char_val' is never used. [unusedStructMember]
         */
        char char_val;
        /* Possible weaknesses found:
         *  union member 'Anonymous0::ptr_val' is never used. [unusedStructMember]
         */
        void *ptr_val;
    } value;
} TupleElement;

typedef struct {
    TupleElement *elements;
    size_t count;
} Tuple;

bool check_tuple_homogeneous(const Tuple *t) {
    if (t == NULL || t->elements == NULL) {
        return false;
    }

    if (t->count == 0) {
        return true;
    }

    DataType first_type = t->elements[0].type;

    for (size_t i = 1; i < t->count; ++i) {
        if (t->elements[i].type != first_type) {
            return false;
        }
    }

    return true;
}

int main(void) {
    TupleElement hom_elements[] = {
        {.type = TYPE_INT, .value.int_val = 1},
        {.type = TYPE_INT, .value.int_val = 2},
        {.type = TYPE_INT, .value.int_val = 3}
    };
    Tuple hom_tuple = {.elements = hom_elements, .count = 3};

    TupleElement het_elements[] = {
        {.type = TYPE_INT, .value.int_val = 1},
        {.type = TYPE_FLOAT, .value.float_val = 2.5f},
        {.type = TYPE_INT, .value.int_val = 3}
    };
    Tuple het_tuple = {.elements = het_elements, .count = 3};

    Tuple empty_tuple = {.elements = NULL, .count = 0};

    printf("%d\n", check_tuple_homogeneous(&hom_tuple));
    printf("%d\n", check_tuple_homogeneous(&het_tuple));
    printf("%d\n", check_tuple_homogeneous(&empty_tuple));

    return 0;
}