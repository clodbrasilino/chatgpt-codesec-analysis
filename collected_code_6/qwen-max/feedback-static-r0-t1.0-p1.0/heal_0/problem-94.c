#include <stdio.h>
#include <limits.h>

typedef struct {
    int index;
    int value;
} Tuple;

Tuple extractMinIndexValue(Tuple *tuples, int size) {
    if (size <= 0) return (Tuple){-1, INT_MAX};

    Tuple min = tuples[0];
    for (int i = 1; i < size; ++i) {
        if (tuples[i].value < min.value) {
            min = tuples[i];
        }
    }
    return min;
}

int main() {
    Tuple tuples[] = {{0, 10}, {1, 5}, {2, 7}, {3, 3}};
    int size = 4;
    Tuple result = extractMinIndexValue(tuples, size);
    printf("Min Index: %d, Min Value: %d\n", result.index, result.value);
    return 0;
}