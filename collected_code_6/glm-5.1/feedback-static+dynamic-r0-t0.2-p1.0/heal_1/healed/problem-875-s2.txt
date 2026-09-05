#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_min_difference(const int *tuples, size_t size) {
    if (tuples == NULL || size < 2) {
        return -1;
    }

    int min_diff = INT_MAX;

    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = i + 1; j < size; j++) {
            int diff = abs(tuples[i] - tuples[j]);
            if (diff < min_diff) {
                min_diff = diff;
            }
        }
    }

    return min_diff;
}

int main(void) {
    int data[] = {1, 5, 3, 19, 18, 25};
    size_t n = sizeof(data) / sizeof(data[0]);

    int result = find_min_difference(data, n);

    printf("%d\n", result);

    return 0;
}