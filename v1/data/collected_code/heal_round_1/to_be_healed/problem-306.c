#include <stdio.h>

int findMaxSum(int arr[], int n, int k) {
    int maxSum = 0;
    int prefixSum = 0;
    int tempSum = 0;
    int i, j;
  
    for (i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        prefixSum = arr[i];
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        tempSum = arr[i];
  
        for (j = i + 1; j < n; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[j-1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'arr[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (arr[j] > arr[j - 1]) {
                /* Possible weaknesses found:
                 *  Cannot determine that 'arr[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 */
                tempSum += arr[j];
                prefixSum += tempSum;
            } else {
                break;
            }
        }
  
        if (tempSum > maxSum && i + k < n) {
            maxSum = tempSum;
        }
    }
  
    return maxSum;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 6;
    int maxSum = findMaxSum(arr, n, k);
  
    printf("Maximum sum of increasing subsequence from prefix till %dth index and including %dth element: %d\n", k, k, maxSum);
  
    return 0;
}