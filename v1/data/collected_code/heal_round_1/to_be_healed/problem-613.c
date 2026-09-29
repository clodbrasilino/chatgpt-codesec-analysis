#include <stdio.h>

int findMaxValue(int tuples[][2], int numTuples) {
    /* Possible weaknesses found:
     *  Cannot determine that 'tuples[0][1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int maxVal = tuples[0][1];
    for (int i = 1; i < numTuples; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'tuples[i][1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (tuples[i][1] > maxVal) {
            /* Possible weaknesses found:
             *  Cannot determine that 'tuples[i][1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            maxVal = tuples[i][1];
        }
    }
    return maxVal;
}

int main() {
    int tuples[][2] = {{5, 10}, {8, 15}, {3, 7}, {2, 20}};
    int numTuples = sizeof(tuples) / sizeof(tuples[0]);

    int maxVal = findMaxValue(tuples, numTuples);
    printf("Maximum value in the tuple list: %d\n", maxVal);

    return 0;
}