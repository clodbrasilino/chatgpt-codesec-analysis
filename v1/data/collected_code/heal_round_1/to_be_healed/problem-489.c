#include <stdio.h>

int findFrequencyOfLargest(int arr[], int size) {
    /* Possible weaknesses found:
     *  Cannot determine that 'arr[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int largest = arr[0];
    int frequency = 0;

    for (int i = 1; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[i] > largest) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            largest = arr[i];
            frequency = 1;
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        } else if (arr[i] == largest) {
            frequency++;
        }
    }

    return frequency;
}

int main() {
    int arr[] = {2, 3, 5, 5, 2, 5, 7, 7, 2, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Frequency of largest value: %d\n", findFrequencyOfLargest(arr, size));

    return 0;
}