#include <stdio.h>

int findLargestPositiveNumber(int arr[], int size) {
    int max = 0;
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[i] > max) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            max = arr[i];
        }
    }
    return max;
}

int main() {
    int arr[] = {5, -8, 12, -3, 9, -1};
    int size = sizeof(arr) / sizeof(arr[0]);
    int largestPositiveNumber = findLargestPositiveNumber(arr, size);
    printf("Largest positive number: %d", largestPositiveNumber);
    return 0;
}