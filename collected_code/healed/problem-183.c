#include <stdio.h>

int countPairsWithDifferenceK(const int arr[], int n, int k) {
    int count = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] - arr[j] == k || arr[j] - arr[i] == k) {
                count++;
            }
        }
    }
    
    return count;
}

int main() {
    int arr[] = {1, 5, 3, 4, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 2;
    
    int distinctPairsCount = countPairsWithDifferenceK(arr, n, k);
    
    printf("Number of distinct pairs with a difference of %d: %d\n", k, distinctPairsCount);
    
    return 0;
}