#include <stdio.h>

typedef struct {
    int *elements;
    int size;
} Tuple;

int checkTupleSize(Tuple tuple, int k) {
    return tuple.size == k;
}

int main() {
    int elements[5] = {1, 2, 3, 4, 5};
    Tuple tuple;
    tuple.elements = elements;
    tuple.size = sizeof(elements) / sizeof(elements[0]);

    int k = 5;
    if (checkTupleSize(tuple, k)) {
        printf("The tuple contains exactly %d elements.\n", k);
    } else {
        printf("The tuple does not contain exactly %d elements.\n", k);
    }

    return 0;
}