#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to join tuples if they have similar initial elements
void joinTuples(int tuples[][2], int numTuples) {
    int i, j, k;
    
    // Sort the tuples based on their initial elements
    for (i = 0; i < numTuples-1; i++) {
        for (j = 0; j < numTuples-i-1; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'tuples[j][0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'tuples[j+1][0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (tuples[j][0] > tuples[j+1][0]) {
                int temp[2];
                /* Possible weaknesses found:
                 *  Cannot determine that 'temp[0]' is initialized [premium-bughuntingUninit]
                 *  Cannot determine that 'tuples[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 */
                memcpy(temp, tuples[j], sizeof(temp));
                /* Possible weaknesses found:
                 *   Does not check for buffer overflows when copying to destination (CWE-120).  Make sure destination can always hold the source data.
                 *  Cannot determine that 'tuples[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 *  Cannot determine that 'tuples[j+1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 */
                memcpy(tuples[j], tuples[j+1], sizeof(temp));
                /* Possible weaknesses found:
                 *   Does not check for buffer overflows when copying to destination (CWE-120).  Make sure destination can always hold the source data.
                 *  Cannot determine that 'tuples[j+1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 */
                memcpy(tuples[j+1], temp, sizeof(temp));
            }
        }
    }
    
    // Merge the tuples with similar initial elements
    for (i = 0, k = 0; i < numTuples; i = j) {
        /* Possible weaknesses found:
         *  Cannot determine that 'tuples[i][0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        tuples[k][0] = tuples[i][0];
        tuples[k][1] = tuples[i][1];
        j = i + 1;
        while (j < numTuples && tuples[j][0] == tuples[i][0]) {
            tuples[k][1] += tuples[j][1];
            j++;
        }
        k++;
    }
    
    // Print the joined tuples
    for (i = 0; i < k; i++) {
        printf("(%d, %d)\n", tuples[i][0], tuples[i][1]);
    }
}

int main() {
    int tuples[][2] = {
        {1, 5},
        {2, 3},
        {1, 2},
        {3, 4},
        {2, 1}
    };
    int numTuples = sizeof(tuples) / sizeof(tuples[0]);
    
    joinTuples(tuples, numTuples);
    
    return 0;
}