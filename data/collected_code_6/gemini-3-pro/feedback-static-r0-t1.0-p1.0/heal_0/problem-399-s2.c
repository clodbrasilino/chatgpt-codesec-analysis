#include <stdio.h>
#include <stdlib.h>

struct Tuple {
    int a;
    int b;
};

int* bitwise_xor_tuples(const struct Tuple* tuples, size_t num_tuples) {
    if (tuples == NULL || num_tuples == 0) {
        return NULL;
    }

    int* results = (int*)malloc(num_tuples * sizeof(int));
    if (results == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < num_tuples; ++i) {
        results[i] = tuples[i].a ^ tuples[i].b;
    }

    return results;
}

int main(void) {
    struct Tuple tuples[] = {
        {10, 5},
        {7, 3},
        {15, 15},
        {0, 255}
    };
    
    size_t num_tuples = sizeof(tuples) / sizeof(tuples[0]);
    
    int* results = bitwise_xor_tuples(tuples, num_tuples);
    if (results != NULL) {
        for (size_t i = 0; i < num_tuples; ++i) {
            printf("%d ^ %d = %d\n", tuples[i].a, tuples[i].b, results[i]);
        }
        free(results);
    } else {
        fprintf(stderr, "Failed to allocate memory or invalid input.\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}