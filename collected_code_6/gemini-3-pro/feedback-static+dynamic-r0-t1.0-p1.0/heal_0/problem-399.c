#include <stdio.h>
#include <stdlib.h>

struct Tuple {
    int a;
    int b;
};

int* bitwise_xor_tuples(const struct Tuple* tuples, size_t count) {
    if (tuples == NULL || count == 0) {
        return NULL;
    }

    int* results = (int*)malloc(count * sizeof(int));
    if (results == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; i++) {
        results[i] = tuples[i].a ^ tuples[i].b;
    }

    return results;
}

int main(void) {
    struct Tuple tuples[] = {
        {5, 3},
        {10, 12},
        {255, 0},
        {15, 15}
    };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);

    int* results = bitwise_xor_tuples(tuples, count);

    if (results != NULL) {
        for (size_t i = 0; i < count; i++) {
            printf("%d ^ %d = %d\n", tuples[i].a, tuples[i].b, results[i]);
        }
        free(results);
    } else {
        printf("Memory allocation failed or invalid input.\n");
    }

    return 0;
}