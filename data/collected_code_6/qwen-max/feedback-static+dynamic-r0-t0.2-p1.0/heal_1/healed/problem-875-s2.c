#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int minDifference(const int *tuples, int size) {
    if (size < 2) return -1;
    
    int min_diff = INT_MAX;
    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
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
    int size = sizeof(tuples) / sizeof(tuples[0]);
    int result = minDifference(tuples, size);
    printf("Minimum difference: %d\n", result);
    return 0;
}