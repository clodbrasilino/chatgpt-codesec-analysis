#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int first;
    int second;
} Tuple;

int min_diff(Tuple *tuples, int n) {
    if (n <= 1) return -1;

    int min_diff = INT_MAX;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int diff = abs(tuples[i].first - tuples[j].first) + abs(tuples[i].second - tuples[j].second);
            if (diff < min_diff) {
                min_diff = diff;
            }
        }
    }

    return (min_diff == INT_MAX) ? -1 : min_diff;
}

int main() {
    Tuple tuples[] = {{1, 2}, {4, 2}, {7, 8}, {5, 3}};
    int n = sizeof(tuples) / sizeof(tuples[0]);
    int result = min_diff(tuples, n);
    if (result != -1) {
        printf("Minimum difference in tuple pairs: %d\n", result);
    } else {
        printf("No valid tuple pairs found.\n");
    }
    return 0;
}