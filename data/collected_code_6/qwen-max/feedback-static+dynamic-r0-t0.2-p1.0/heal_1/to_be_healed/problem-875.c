#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'tuples' can be declared as pointer to const [constParameterPointer]
 */
int minDifference(int *tuples, int n) {
    if (n < 2) return -1;
    int min_diff = INT_MAX;
    for (int i = 0; i < n-1; i++) {
        for (int j = i + 1; j < n; j++) {
            int diff = abs(tuples[i] - tuples[j]);
            if (diff < min_diff) {
                min_diff = diff;
            }
        }
    }
    return min_diff == INT_MAX ? -1 : min_diff;
}

int main() {
    int tuples[] = {4, 9, 1, 3, 7};
    int n = sizeof(tuples) / sizeof(tuples[0]);
    int result = minDifference(tuples, n);
    if (result != -1) {
        printf("Minimum difference: %d\n", result);
    } else {
        printf("Not enough elements to compare.\n");
    }
    return 0;
}