#include <stdio.h>

void removeEmptyTuple(int tuples[][2], int *sizePtr) {
    int newSize = 0;
    /* Possible weaknesses found:
     *  Cannot determine that '*sizePtr' is initialized [premium-bughuntingUninit]
     */
    for (int i = 0; i < *sizePtr; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'tuples[i][1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'tuples[i][0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (tuples[i][0] != 0 && tuples[i][1] != 0) {
            /* Possible weaknesses found:
             *  Cannot determine that 'tuples[i][0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            tuples[newSize][0] = tuples[i][0];
            tuples[newSize][1] = tuples[i][1];
            newSize++;
        }
    }
    *sizePtr = newSize;
}

int main() {
    int tuples[5][2] = { {1, 2}, {0, 0}, {3, 4}, {0, 0}, {5, 6} };
    int size = 5;

    removeEmptyTuple(tuples, &size);

    for (int i = 0; i < size; i++) {
        printf("(%d, %d) ", tuples[i][0], tuples[i][1]);
    }

    return 0;
}