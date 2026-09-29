#include <stdio.h>

void splitAndAdd(int arr[], int n, int k) {
    int temp[k];
    
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    for (int i = 0; i < k; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        temp[i] = arr[i];
    }
    
    for (int i = 0; i < n - k; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i+k]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        arr[i] = arr[i + k];
    }
    
    for (int i = n - k, j = 0; i < n; i++, j++) {
        arr[i] = temp[j];
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 2;
    
    splitAndAdd(arr, n, k);
    
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    
    return 0;
}