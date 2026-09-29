#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

struct Tuple {
    int a;
    int b;
};

int xor_tuples(const struct Tuple* tuples, size_t count) {
    if (tuples == NULL || count == 0) {
        return 0;
    }

    int result = 0;
    for (size_t i = 0; i < count; i++) {
        result ^= tuples[i].a;
        result ^= tuples[i].b;
    }

    return result;
}

int main(void) {
    size_t count = 3;
    struct Tuple* tuples = (struct Tuple*)malloc(count * sizeof(struct Tuple));
    
    if (tuples == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    tuples[0].a = 5;
    tuples[0].b = 10;
    tuples[1].a = 15;
    tuples[1].b = 20;
    tuples[2].a = 25;
    tuples[2].b = 30;

    int result = xor_tuples(tuples, count);
    
    printf("Result of bitwise XOR across tuples: %d\n", result);

    free(tuples);
    tuples = NULL;

    return EXIT_SUCCESS;
}