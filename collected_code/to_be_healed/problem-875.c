#include <stdio.h>
#include <stdlib.h>

int minDifference(int tuple1[], int tuple2[], int size) {
    /* Possible weaknesses found:
     *  Cannot determine that 'tuple1[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *  Cannot determine that 'tuple2[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int minDiff = abs(tuple1[0] - tuple2[0]);
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'tuple2[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'tuple1[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        int diff = abs(tuple1[i] - tuple2[i]);
        if (diff < minDiff) {
            minDiff = diff;
        }
    }
    return minDiff;
}

int main() {
    int tuple1[] = {1, 8, 3};
    int tuple2[] = {5, 2, 7};
    int size = sizeof(tuple1) / sizeof(tuple1[0]);
    int minDiff = minDifference(tuple1, tuple2, size);
    printf("Minimum difference: %d\n", minDiff);
    return 0;
}