#include <stdio.h>
#include <stdlib.h>

int minSubsetsWithDistinctElements(const int *arr, int n) {
    int max = 0;
    for (int i = 0; i < n; ++i) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    int *freq = (int *)calloc(max + 1, sizeof(int));
    for (int i = 0; i < n; ++i) {
        freq[arr[i]]++;
    }

    int maxFreq = 0;
    for (int i = 0; i <= max; ++i) {
        if (freq[i] > maxFreq) {
            maxFreq = freq[i];
        }
    }

    free(freq);

    return maxFreq;
}

int main() {
    int arr[] = {1, 2, 3, 2, 4, 1, 5, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = minSubsetsWithDistinctElements(arr, n);
    printf("Minimum number of subsets with distinct elements: %d\n", result);
    return 0;
}