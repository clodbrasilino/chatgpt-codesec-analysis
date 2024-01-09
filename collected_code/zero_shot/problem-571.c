#include <stdio.h>

int maxSumDisjointPairs(int arr[], int n, int k) {
    int maxSum = 0;
    int pairCount = 0;
    
    // Sort the array in non-decreasing order
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    
    // Find maximum sum of disjoint pairs
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] == arr[i + 1]) {
            maxSum += arr[i];
            pairCount++;
            
            // Skip elements that are the same to avoid repeating pairs
            while (arr[i] == arr[i + 1])
                i++;
        }
    }
    
    return maxSum * k;
}

int main() {
    int arr[] = {1, 3, 2, 2, 4, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 2;
    
    int maxSum = maxSumDisjointPairs(arr, n, k);
    
    printf("Maximum sum of disjoint pairs: %d\n", maxSum);
    
    return 0;
}