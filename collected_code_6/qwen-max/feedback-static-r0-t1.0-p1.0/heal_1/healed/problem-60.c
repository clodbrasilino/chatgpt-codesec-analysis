#include <stdio.h>
#include <stdlib.h>

int maxSubsequenceLength(const int *arr, int n) {
    if (n <= 1) return n;
    
    int maxLen = 1, currentDiff = arr[1] - arr[0], currentLen = 1;
    
    for (int i = 2; i < n; i++) {
        if (arr[i] - arr[i-1] == currentDiff) {
            currentLen++;
        } else {
            currentDiff = arr[i] - arr[i-1];
            currentLen = 2;
        }
        if (currentLen > maxLen) {
            maxLen = currentLen;
        }
    }
    
    return maxLen;
}

int main() {
    const int arr[] = {1, 2, 3, 5, 7, 9, 11};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int result = maxSubsequenceLength(arr, n);
    printf("Maximum length of subsequence: %d\n", result);
    
    return 0;
}