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
        return 0;
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
    elems1[1].value = 2;

    TupleElement elems2[] = {{0, 1}, {1, 0}, {0, 3}};
    Tuple tuple2 = {elems2, 3};
    elems2[1].value = 0;

    Tuple tuple3 = {NULL, 0};

    printf("%d\n", has_none_value(&tuple1));
    printf("%d\n", has_none_value(&tuple2));
    printf("%d\n", has_none_value(&tuple3));
    printf("%d\n", has_none_value(NULL));

    return 0;
}