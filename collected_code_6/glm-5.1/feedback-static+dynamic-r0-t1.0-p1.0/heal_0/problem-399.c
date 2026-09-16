#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

int xor_tuples(const Tuple *tuples, size_t count, int *result) {
    if (tuples == NULL || result == NULL) {
        return -1;
    }

    if (count == 0) {
        return -1;
    }

    *result = tuples[0].a ^ tuples[0].b;

    for (size_t i = 1; i < count; i++) {
        *result ^= (tuples[i].a ^ tuples[i].b);
    }

    return 0;
}

int main(void) {
    Tuple data[] = {{12, 10}, {7, 5}, {3, 9}};
    size_t num_tuples = sizeof(data) / sizeof(data[0]);
    int final_result;

    if (xor_tuples(data, num_tuples, &final_result) == 0) {
        printf("%d\n", final_result);
    } else {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}