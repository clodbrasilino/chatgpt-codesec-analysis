#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int min_diff_in_tuples(int *tuples, int n) {
    if (n < 2) return -1;
    
    int min_diff = INT_MAX;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int diff = abs(tuples[i] - tuples[j]);
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
    int result = min_diff_in_tuples(tuples, n);
    printf("Minimum difference: %d\n", result);
    return 0;
}