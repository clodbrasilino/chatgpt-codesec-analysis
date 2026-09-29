#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int sumAlternateChains(Tuple* tuples, size_t size) {
    if (tuples == NULL || size == 0) {
        return 0;
    }

    int sum = 0;
    for (size_t i = 0; i < size; i += 2) {
        sum += tuples[i].first + tuples[i].second;
    }

    return sum;
}

int main() {
    size_t size = 5;
    Tuple* tuples = (Tuple*)malloc(size * sizeof(Tuple));
    if (tuples == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (size_t i = 0; i < size; ++i) {
        tuples[i].first = (int)(i + 1);
        tuples[i].second = (int)(i + 2);
    }

    int result = sumAlternateChains(tuples, size);
    printf("Sum of alternate chains: %d\n", result);

    free(tuples);
    tuples = NULL;

    return 0;
}