#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int x;
    int y;
} Tuple;

int find_max_difference(const Tuple *tuples, size_t count, int *max_diff) {
    if (tuples == NULL || max_diff == NULL || count == 0) {
        return -1;
    }

    int max = INT_MIN;
    size_t i;

    for (i = 0; i < count; i++) {
        int diff = abs(tuples[i].x - tuples[i].y);
        if (diff > max) {
            max = diff;
        }
    }

    *max_diff = max;
    return 0;
}

int main(void) {
    Tuple tuples[] = {{1, 5}, {3, 8}, {10, 2}, {4, 4}};
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    int max_diff;

    if (find_max_difference(tuples, count, &max_diff) == 0) {
        printf("Maximum difference: %d\n", max_diff);
    } else {
        fprintf(stderr, "Error calculating maximum difference\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}