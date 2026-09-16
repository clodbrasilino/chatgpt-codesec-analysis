#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

long long cumulative_sum(const Tuple *tuples, size_t count) {
    long long sum = 0;
    if (tuples == NULL) {
        return 0;
    }
    for (size_t i = 0; i < count; i++) {
        if (tuples[i].data == NULL) {
            continue;
        }
        for (size_t j = 0; j < tuples[i].size; j++) {
            sum += tuples[i].data[j];
        }
    }
    return sum;
}

int main(void) {
    int a[] = {1, 2, 3};
    int b[] = {4, 5};
    int c[] = {6, 7, 8, 9};

    Tuple tuples[] = {
        {a, 3},
        {b, 2},
        {c, 4}
    };

    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    long long result = cumulative_sum(tuples, count);
    printf("Cumulative sum: %lld\n", result);

    return 0;
}