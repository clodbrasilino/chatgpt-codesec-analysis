#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_min_difference(const int *tuples, size_t size) {
    if (tuples == NULL || size < 2) {
        return -1;
    }

    int min_diff = INT_MAX;

    for (size_t i = 0; i < size - 1; i++) {
        int diff = abs(tuples[i] - tuples[i + 1]);
        if (diff < min_diff) {
            min_diff = diff;
        }
    }

    return min_diff;
}

int main(void) {
    int data[] = {10, 15, 3, 8, 12};
    size_t n = sizeof(data) / sizeof(data[0]);

    int result = find_min_difference(data, n);

    printf("%d\n", result);

    return 0;
}