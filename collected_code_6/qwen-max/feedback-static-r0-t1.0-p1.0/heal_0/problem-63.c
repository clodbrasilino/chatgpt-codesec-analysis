#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int first;
    int second;
} Tuple;

int findMaxDifference(Tuple *tuples, int size) {
    int max_diff = INT_MIN;
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            int diff = tuples[i].first - tuples[j].second;
            if (diff > max_diff) {
                max_diff = diff;
            }
            diff = tuples[i].second - tuples[j].first;
            if (diff > max_diff) {
                max_diff = diff;
            }
            diff = tuples[j].first - tuples[i].second;
            if (diff > max_diff) {
                max_diff = diff;
            }
            diff = tuples[j].second - tuples[i].first;
            if (diff > max_diff) {
                max_diff = diff;
            }
        }
    }
    return max_diff;
}

int main() {
    Tuple tuples[] = {{3, 5}, {1, 8}, {6, 2}};
    int size = sizeof(tuples) / sizeof(tuples[0]);
    int max_diff = findMaxDifference(tuples, size);
    printf("Maximum difference: %d\n", max_diff);
    return 0;
}