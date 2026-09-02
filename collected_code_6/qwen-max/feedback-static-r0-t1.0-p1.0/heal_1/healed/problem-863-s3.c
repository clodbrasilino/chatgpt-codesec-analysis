#include <stdio.h>
#include <stdlib.h>

int longestConsecutive(const int *arr, int n) {
    if (n <= 0) return 0;

    int min = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }

    int *hash = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; ++i) {
        hash[arr[i] - min] = 1;
    }

    int maxLength = 0;
    int currentLength = 0;
    for (int i = 0; i < n; ++i) {
        if (hash[i] == 1) {
            currentLength++;
            if (currentLength > maxLength) {
                maxLength = currentLength;
            }
        } else {
            currentLength = 0;
        }
    }

    free(hash);
    return maxLength;
}

int main() {
    int arr[] = {13, 2, 3, 14, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = longestConsecutive(arr, n);
    printf("Length of the longest consecutive subsequence is %d\n", result);
    return 0;
}