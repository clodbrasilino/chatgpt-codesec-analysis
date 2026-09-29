#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int first;
    int second;
} Tuple;

int maxDifference(Tuple *tuples, size_t count) {
    int min_val = INT_MAX;
    int max_diff = 0;
    for (size_t i = 0; i < count; ++i) {
        if (tuples[i].first < min_val) {
            min_val = tuples[i].first;
        }
        if (tuples[i].second > min_val && (tuples[i].second - min_val) > max_diff) {
            max_diff = tuples[i].second - min_val;
        }
        if (tuples[i].first > min_val && (tuples[i].first - min_val) > max_diff) {
            max_diff = tuples[i].first - min_val;
        }
    }
    return max_diff;
}

int main() {
    Tuple tuples[] = {{2, 5}, {9, 11}, {3, 4}, {8, 1}};
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    int result = maxDifference(tuples, count);
    printf("Maximum difference: %d\n", result);
    return 0;
}