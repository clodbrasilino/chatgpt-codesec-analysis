#include <stdio.h>

int maxProduct(int arr[], int n) {
    int result = -1;
    int product = 1;
    
    for (int i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'arr[i+1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[i] < arr[i+1]) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            product *= arr[i];
        }
        else {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            product *= arr[i];
            if (product > result) {
                result = product;
            }
            product = 1;
        }
    }
    
    return result;
}

int main() {
    int arr[] = {3, 2, 5, 4, 7, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Maximum product: %d\n", maxProduct(arr, n));
    
    return 0;
}