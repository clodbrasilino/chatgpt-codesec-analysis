#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int sumAlternateChains(Tuple* tuples, size_t size, int chainIndex) {
    if (tuples == NULL || size == 0) {
        return 0;
    }

    int sum = 0;
    for (size_t i = 0; i < size; ++i) {
        if (chainIndex == 0) {
            sum += tuples[i].first;
        } else if (chainIndex == 1) {
            sum += tuples[i].second;
        }
    }
    return sum;
}

int main(void) {
    size_t size = 4;
    Tuple* tuples = (Tuple*)malloc(size * sizeof(Tuple));
    if (tuples == NULL) {
        return 1;
    }

    tuples[0] = (Tuple){1, 2};
    tuples[1] = (Tuple){3, 4};
    tuples[2] = (Tuple){5, 6};
    tuples[3] = (Tuple){7, 8};

    int sumFirst = sumAlternateChains(tuples, size, 0);
    int sumSecond = sumAlternateChains(tuples, size, 1);

    printf("%d\n", sumFirst);
    printf("%d\n", sumSecond);

    free(tuples);
    tuples = NULL;

    return 0;
}