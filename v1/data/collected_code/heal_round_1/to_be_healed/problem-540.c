#include <stdio.h>

int findMax(int arr[], int size) {
    /* Possible weaknesses found:
     *  Cannot determine that 'arr[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int max = arr[0];
    for(int i = 1; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if(arr[i] > max) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            max = arr[i];
        }
    }
    return max;
}

int findMin(int arr[], int size) {
    /* Possible weaknesses found:
     *  Cannot determine that 'arr[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int min = arr[0];
    for(int i = 1; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if(arr[i] < min) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            min = arr[i];
        }
    }
    return min;
}

int findDifference(int arr[], int size) {
    int maxVal = findMax(arr, size);
    int minVal = findMin(arr, size);
    int maxCount = 0;
    int minCount = 0;
    
    for(int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if(arr[i] == maxVal) {
            maxCount++;
        }
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if(arr[i] == minVal) {
            minCount++;
        }
    }
    
    return maxCount - minCount;
}

int main() {
    int arr[] = {2, 2, 3, 4, 4, 4, 5, 5, 5, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    int difference = findDifference(arr, size);
    printf("Difference between highest and least frequencies: %d", difference);
    
    return 0;
}