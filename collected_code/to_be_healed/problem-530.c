#include <stdio.h>

float findNegativeRatio(int arr[], int size) {
    int negativeCount = 0;
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[i] < 0) {
            negativeCount++;
        }
    }
    return (float) negativeCount / size;
}