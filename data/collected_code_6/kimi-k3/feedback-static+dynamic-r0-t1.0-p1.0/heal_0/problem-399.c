#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t length;
} Tuple;

int tuple_xor(const Tuple *tuple, int *result) {
    size_t i;
    int xor_value = 0;

    if (tuple == NULL || result == NULL) {
        return -1;
    }

    if (tuple->length > 0 && tuple->elements == NULL) {
        return -1;
    }

    for (i = 0; i < tuple->length; i++) {
        xor_value ^= tuple->elements[i];
    }

    *result = xor_value;
    return 0;
}

int main(void) {
    int data1[] = {5, 3, 9, 1};
    int data2[] = {7, 7, 7, 7};
    int data3[] = {12};
    Tuple tuple1;
    Tuple tuple2;
    Tuple tuple3;
    int result = 0;

    tuple1.elements = data1;
    tuple1.length = sizeof(data1) / sizeof(data1[0]);

    tuple2.elements = data2;
    tuple2.length = sizeof(data2) / sizeof(data2[0]);

    tuple3.elements = data3;
    tuple3.length = sizeof(data3) / sizeof(data3[0]);

    if (tuple_xor(&tuple1, &result) == 0) {
        printf("XOR of tuple1: %d\n", result);
    } else {
        fprintf(stderr, "Error computing XOR for tuple1\n");
        return EXIT_FAILURE;
    }

    if (tuple_xor(&tuple2, &result) == 0) {
        printf("XOR of tuple2: %d\n", result);
    } else {
        fprintf(stderr, "Error computing XOR for tuple2\n");
        return EXIT_FAILURE;
    }

    if (tuple_xor(&tuple3, &result) == 0) {
        printf("XOR of tuple3: %d\n", result);
    } else {
        fprintf(stderr, "Error computing XOR for tuple3\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}