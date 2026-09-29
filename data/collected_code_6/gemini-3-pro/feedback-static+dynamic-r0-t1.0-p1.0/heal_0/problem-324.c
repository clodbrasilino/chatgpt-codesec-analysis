#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int sumAlternateChains(Tuple* tuples, int size) {
    if (tuples == NULL || size <= 0) {
        return 0;
    }

    int sum = 0;
    for (int i = 0; i < size; i += 2) {
        sum += tuples[i].first + tuples[i].second;
    }

    return sum;
}

int main(void) {
    int size = 5;
    Tuple* tuples = (Tuple*)malloc((size_t)size * sizeof(Tuple));
    if (tuples == NULL) {
        return 1;
    }

    for (int i = 0; i < size; i++) {
        tuples[i].first = i + 1;
        tuples[i].second = (i + 1) * 2;
    }

    int result = sumAlternateChains(tuples, size);
    printf("Sum: %d\n", result);

    free(tuples);
    tuples = NULL;

    return 0;
}