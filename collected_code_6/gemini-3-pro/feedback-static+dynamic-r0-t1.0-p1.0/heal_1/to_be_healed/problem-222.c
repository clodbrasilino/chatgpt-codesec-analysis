#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_CHAR,
    TYPE_STRING
} DataType;

typedef struct {
    DataType type;
    /* Possible weaknesses found:
     *  struct member 'TupleElement::value' is never used. [unusedStructMember]
     */
    void *value;
} TupleElement;

bool check_same_type(const TupleElement *tuple, size_t size) {
    if (tuple == NULL || size == 0) {
        return false;
    }

    if (size == 1) {
        return true;
    }

    DataType first_type = tuple[0].type;

    for (size_t i = 1; i < size; i++) {
        if (tuple[i].type != first_type) {
            return false;
        }
    }

    return true;
}

int main(void) {
    int val1 = 10;
    int val2 = 20;
    int val3 = 30;
    float val4 = 1.5f;

    TupleElement tuple1[] = {
        {TYPE_INT, &val1},
        {TYPE_INT, &val2},
        {TYPE_INT, &val3}
    };

    TupleElement tuple2[] = {
        {TYPE_INT, &val1},
        {TYPE_FLOAT, &val4},
        {TYPE_INT, &val3}
    };

    size_t size1 = sizeof(tuple1) / sizeof(tuple1[0]);
    size_t size2 = sizeof(tuple2) / sizeof(tuple2[0]);

    if (check_same_type(tuple1, size1)) {
        printf("tuple1: All elements have the same data type.\n");
    } else {
        printf("tuple1: Elements have different data types.\n");
    }

    if (check_same_type(tuple2, size2)) {
        printf("tuple2: All elements have the same data type.\n");
    } else {
        printf("tuple2: Elements have different data types.\n");
    }

    return 0;
}