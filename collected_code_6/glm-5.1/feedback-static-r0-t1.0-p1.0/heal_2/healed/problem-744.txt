#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int is_none;
    int value;
} TupleElement;

typedef struct {
    TupleElement *elements;
    size_t count;
} Tuple;

int has_none_value(const Tuple *tuple) {
    if (tuple == NULL) {
        return 0;
    }

    if (tuple->elements == NULL) {
        return tuple->count == 0;
    }

    for (size_t i = 0; i < tuple->count; i++) {
        if (tuple->elements[i].is_none) {
            return 1;
        }
    }

    return 0;
}

int main(void) {
    TupleElement elems1[] = {{0, 1}, {0, 2}, {0, 3}};
    Tuple tuple1 = {elems1, 3};

    TupleElement elems2[] = {{0, 1}, {1, 5}, {0, 3}};
    Tuple tuple2 = {elems2, 3};

    Tuple tuple3 = {NULL, 0};

    (void)tuple1.elements[0].value;
    (void)tuple2.elements[0].value;

    printf("%d\n", has_none_value(&tuple1));
    printf("%d\n", has_none_value(&tuple2));
    printf("%d\n", has_none_value(&tuple3));
    printf("%d\n", has_none_value(NULL));

    return 0;
}