#include <stdio.h>

int max(int x, int y) {
    return (x > y) ? x : y;
}

int bitonicMaxSum(int arr[], int n) {
    int asc[n]; // stores the maximum sum in increasing subsequence ending at arr[i]
    int desc[n]; // stores the maximum sum in decreasing subsequence starting at arr[i]
    
    // calculate the maximum sum in increasing subsequence ending at arr[i]
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    for (int i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        asc[i] = arr[i];
        for (int j = 0; j < i; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'arr[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (arr[i] > arr[j]) {
                /* Possible weaknesses found:
                 *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 */
                asc[i] = max(asc[i], asc[j] + arr[i]);
            }
        }
    }
    
    // calculate the maximum sum in decreasing subsequence starting at arr[i]
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    for (int i = n - 1; i >= 0; i--) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        desc[i] = arr[i];
        for (int j = n - 1; j > i; j--) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'arr[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (arr[i] > arr[j]) {
                /* Possible weaknesses found:
                 *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 */
                desc[i] = max(desc[i], desc[j] + arr[i]);
            }
        }
    }
    
    // find the maximum sum of bi-tonic sub-sequence
    /* Possible weaknesses found:
     *  Cannot determine that 'asc[0]' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'desc[0]' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'arr[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int maxSum = asc[0] + desc[0] - arr[0];
    for (int i = 1; i < n; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        maxSum = max(maxSum, asc[i] + desc[i] - arr[i]);
    }
    
    return maxSum;
}

int main() {
    int arr[] = {3, 6, 8, 7, 4, 1, 2, 9, 5}; // example array
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int result = bitonicMaxSum(arr, n);
    printf("The maximum sum of bi-tonic sub-sequence is: %d\n", result);
    
    return 0;
}