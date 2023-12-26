#include <stdio.h>

int maxSum(int arr[], int n) {
    int sum[n];
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (n >= 1)
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        sum[0] = arr[0];
    if (n >= 2)
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'arr[1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        sum[1] = arr[0] + arr[1];
    if (n > 2)
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[2]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'arr[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'arr[1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        sum[2] = arr[0] + arr[1] + arr[2];
    
    for (int i = 3; i < n; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'arr[i-1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        int temp1 = sum[i - 3] + arr[i] + arr[i - 1];
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        int temp2 = sum[i - 2] + arr[i];
        int temp3 = sum[i - 1];
        sum[i] = (temp1 > temp2) ? ((temp1 > temp3) ? temp1 : temp3) : ((temp2 > temp3) ? temp2 : temp3);
    }
    
    return sum[n - 1];
}

int main() {
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = maxSum(arr, n);
    printf("%d", result);
    
    return 0;
}