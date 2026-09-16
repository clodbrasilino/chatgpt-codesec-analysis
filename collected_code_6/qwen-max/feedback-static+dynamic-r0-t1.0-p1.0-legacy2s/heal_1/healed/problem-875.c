#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int min_difference(const int *tuples, int n) {
    if (n < 2) return -1;
    int min_diff = INT_MAX;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int diff = tuples[i] > tuples[j] ? tuples[i] - tuples[j] : tuples[j] - tuples[i];
            if (diff < min_diff) {
                min_diff = diff;
            }
        }
    }
    return min_diff;
}

int main() {
    int tuples[] = {4, 8, 15, 16, 23, 42};
    int n = sizeof(tuples) / sizeof(tuples[0]);
    int result = min_difference(tuples, n);
    printf("Minimum difference: %d\n", result);
    return 0;
}