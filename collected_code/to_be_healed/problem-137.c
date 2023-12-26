#include <stdio.h>

float findZeroRatio(int arr[], int size) {
    int zeroes = 0;
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[i] == 0) {
            zeroes++;
        }
    }
    return (float)zeroes / size;
}