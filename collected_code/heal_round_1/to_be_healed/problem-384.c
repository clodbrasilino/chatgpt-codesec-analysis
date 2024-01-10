#include <stdio.h>

int findFrequencyOfSmallestValue(int arr[], int size) {
    /* Possible weaknesses found:
     *  Cannot determine that 'arr[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int smallestValue = arr[0];
    int frequency = 0;
    
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[i] < smallestValue) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            smallestValue = arr[i];
        }
    }
    
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[i] == smallestValue) {
            frequency++;
        }
    }
    
    return frequency;
}

int main() {
    int arr[] = {3, 2, 1, 4, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    int frequency = findFrequencyOfSmallestValue(arr, size);
    
    printf("Frequency of smallest value: %d\n", frequency);
    
    return 0;
}