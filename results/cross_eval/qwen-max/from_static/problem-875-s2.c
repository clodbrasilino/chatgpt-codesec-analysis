#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int findMinimumDifference(const int tuples[], int n) {
    if (n < 2) return -1;
    
    int min_diff = INT_MAX;
    
    for (int i = 0; i < n - 1; i += 2) {
        int diff = abs(tuples[i] - tuples[i + 1]);
        if (diff < min_diff) {
            min_diff = diff;
        }
    }
    
    return min_diff;
}

int main() {
    const int tuples[] = {1, 5, 10, 15, 20, 25, 30, 35};
    int n = sizeof(tuples) / sizeof(tuples[0]);
    
    int result = findMinimumDifference(tuples, n);
    
    if (result != -1) {
        printf("The minimum difference in the tuple pairs is: %d\n", result);
    } else {
        printf("Invalid input.\n");
    }
    
    return 0;
}