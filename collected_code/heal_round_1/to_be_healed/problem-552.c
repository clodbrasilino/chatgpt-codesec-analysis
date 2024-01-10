#include <stdio.h>
#include <stdbool.h>

bool isLinear(int arr[], int size) {
    if (size == 0 || size == 1) {
        return true;
    }
    
    /* Possible weaknesses found:
     *  Cannot determine that 'arr[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *  Cannot determine that 'arr[1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int difference = arr[1] - arr[0];
    
    for (int i = 2; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'arr[i-1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[i] - arr[i-1] != difference) {
            return false;
        }
    }
    
    return true;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5}; // Example sequence
    int size = sizeof(arr) / sizeof(arr[0]);
    
    if (isLinear(arr, size)) {
        printf("The given sequence is linear.\n");
    } else {
        printf("The given sequence is not linear.\n");
    }
    
    return 0;
}