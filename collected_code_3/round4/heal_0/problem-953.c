#include <stdio.h>
#include <stdlib.h>

int minSubsets(int arr[], int n) {
    int max = 0;
    int freq[10000] = {0};

    for (int i = 0; i < n; i++) {
        freq[arr[i]]++;
        if (freq[arr[i]] > max) {
            max = freq[arr[i]];
        }
    }
    return max;
}

int main() {
    int arr[] = {1, 2, 3, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Minimum number of subsets with distinct elements is %d", minSubsets(arr, n));
    return 0;
}