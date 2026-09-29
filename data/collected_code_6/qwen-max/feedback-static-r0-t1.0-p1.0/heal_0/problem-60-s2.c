#include <stdio.h>
#include <stdlib.h>

int maxSubsequenceLength(int *arr, int n) {
    int maxLength = 0;
    for (int i = 0; i < n; ++i) {
        int currentLength = 1;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] - arr[j - 1] == 1) {
                ++currentLength;
            } else {
                break;
            }
        }
        if (currentLength > maxLength) {
            maxLength = currentLength;
        }
    }
    return maxLength;
}

int main() {
    int arr[] = {1, 2, 3, 5, 6, 7, 10, 11};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = maxSubsequenceLength(arr, n);
    printf("Maximum length of subsequence: %d\n", result);
    return 0;
}