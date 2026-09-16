#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int first;
    int second;
} Tuple;

int max_difference_between_pairs(Tuple *tuples, int size) {
    if (tuples == NULL || size <= 0) {
        return INT_MIN;
    }

    int max_first = tuples[0].first;
    int min_second = tuples[0].second;
    int max_diff = INT_MIN;

    for (int i = 0; i < size; i++) {
        if (max_first < tuples[i].first) {
            max_first = tuples[i].first;
        }
        if (min_second > tuples[i].second) {
            min_second = tuples[i].second;
        }
        int diff = tuples[i].first - tuples[i].second;
        if (diff > max_diff) {
            max_diff = diff;
        }
    }

    int cross_diff = max_first - min_second;
    if (cross_diff > max_diff) {
        max_diff = cross_diff;
    }

    return max_diff;
}

int main(void) {
    Tuple tuples[] = {
        {3, 5},
        {10, 2},
        {8, 7},
        {1, 9},
        {6, 4}
    };
    int size = sizeof(tuples) / sizeof(tuples[0]);

    int result = max_difference_between_pairs(tuples, size);

    if (result != INT_MIN) {
        printf("%d\n", result);
    } else {
        printf("Invalid input\n");
    }

    return 0;
}