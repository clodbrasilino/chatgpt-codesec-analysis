#include <stdio.h>
#include <stddef.h>

typedef struct {
    int value;
} Tuple;

int cumulativeSum(const Tuple *tuples, size_t count) {
    int sum = 0;
    for (size_t i = 0; i < count; ++i) {
        sum += tuples[i].value;
    }
    return sum;
}

int main() {
    Tuple tuples[] = {{1}, {2}, {3}, {4}, {5}};
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    int result = cumulativeSum(tuples, count);
    printf("Cumulative sum: %d\n", result);
    return 0;
}