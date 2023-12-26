#include <stdio.h>

int largestNegative(int arr[], int n) {
    int largest = 0;
    
    for(int i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if(arr[i] < 0 && arr[i] < largest) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            largest = arr[i];
        }
    }

    return largest;
}

int main() {
    int arr[] = {5, -7, -3, 0, -10, -2};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int largestNeg = largestNegative(arr, n);
    
    printf("Largest negative number: %d\n", largestNeg);

    return 0;
}