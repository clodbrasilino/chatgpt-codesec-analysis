#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_min_difference(const int *tuples, size_t size) {
    if (tuples == NULL || size < 2) {
        return -1;
    }

    int min_diff = INT_MAX;

    for (size_t i = 0; i < size - 1; i++) {
        int diff = tuples[i + 1] - tuples[i];
        if (diff < 0) {
            diff = -diff;
        }
        if (diff < min_diff) {
            min_diff = diff;
        }
    }

    return min_diff;
}

int main(void) {
    int data[] = {1, 10, 5, 20, 12};
    size_t n = sizeof(data) / sizeof(data[0]);

    int result = find_min_difference(data, n);

    printf("%d\n", result);

    return 0;
}