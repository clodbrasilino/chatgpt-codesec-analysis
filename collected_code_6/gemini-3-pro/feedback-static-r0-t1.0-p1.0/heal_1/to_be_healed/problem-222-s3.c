#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_STRING
} DataType;

typedef struct {
    DataType type;
    union {
        int i_val;
        float f_val;
        /* Possible weaknesses found:
         *  union member 'Anonymous0::d_val' is never used. [unusedStructMember]
         */
        double d_val;
        /* Possible weaknesses found:
         *  union member 'Anonymous0::s_val' is never used. [unusedStructMember]
         */
        char *s_val;
    } value;
} TupleElement;

typedef struct {
    TupleElement *elements;
    size_t length;
} Tuple;

bool have_same_data_type(const Tuple *tuple) {
    if (tuple == NULL || tuple->elements == NULL) {
        return false;
    }

    if (tuple->length <= 1) {
        return true;
    }

    DataType first_type = tuple->elements[0].type;

    for (size_t i = 1; i < tuple->length; i++) {
        if (tuple->elements[i].type != first_type) {
            return false;
        }
    }

    return true;
}

int main(void) {
    TupleElement elements_same[] = {
        {TYPE_INT, .value.i_val = 10},
        {TYPE_INT, .value.i_val = 20},
        {TYPE_INT, .value.i_val = 30}
    };
    Tuple tuple_same = {elements_same, sizeof(elements_same) / sizeof(elements_same[0])};

    TupleElement elements_diff[] = {
        {TYPE_INT, .value.i_val = 10},
        {TYPE_FLOAT, .value.f_val = 3.14f},
        {TYPE_INT, .value.i_val = 30}
    };
    Tuple tuple_diff = {elements_diff, sizeof(elements_diff) / sizeof(elements_diff[0])};

    if (have_same_data_type(&tuple_same)) {
        printf("tuple_same: All elements have the same data type.\n");
    } else {
        printf("tuple_same: Elements have different data types.\n");
    }

    if (have_same_data_type(&tuple_diff)) {
        printf("tuple_diff: All elements have the same data type.\n");
    } else {
        printf("tuple_diff: Elements have different data types.\n");
    }

    return 0;
}