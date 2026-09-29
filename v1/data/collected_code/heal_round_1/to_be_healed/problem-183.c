#include <stdio.h>

int countPairsWithDifferenceK(int arr[], int n, int k) {
    int count = 0;
    
    // Iterate over each element in the array
    for (int i = 0; i < n; i++) {
        // Check if there is any pair with a difference of k
        for (int j = i + 1; j < n; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'arr[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
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