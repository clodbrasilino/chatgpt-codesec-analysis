#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int findFrequencyDifference(const int *arr, int n) {
    int minFreq = INT_MAX;
    int maxFreq = INT_MIN;
    int *freqs = (int *)calloc(n, sizeof(int));
    if (freqs == NULL) {
        return -1;
    }

    for (int i = 0; i < n; ++i) {
        ++freqs[arr[i]];
        if (freqs[arr[i]] > maxFreq) {
            maxFreq = freqs[arr[i]];
        }
    }

    for (int i = 0; i < n; ++i) {
        if (freqs[i] != 0 && freqs[i] < minFreq) {
            minFreq = freqs[i];
        }
    }

    free(freqs);
    return maxFreq - minFreq;
}

int main() {
    int arr[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = findFrequencyDifference(arr, n);
    printf("Difference: %d\n", result);
    return 0;
}