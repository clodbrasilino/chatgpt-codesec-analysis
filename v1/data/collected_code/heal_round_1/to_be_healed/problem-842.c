#include <stdio.h>

int oddOccurrence(int arr[], int size) {
    int result = 0;
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        result ^= arr[i];
    }
    return result;
}

int main() {
    int arr[] = {1, 2, 3, 2, 1, 3, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    int oddNumber = oddOccurrence(arr, size);
    
    printf("Number which occurs odd number of times: %d\n", oddNumber);
    
    return 0;
}