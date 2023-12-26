
#include <stdio.h>

void removeMatchingTuples(int* tuple1, int* tuple2, int length) {
    int result[length][2];
    int k = 0;
    
    for (int i = 0; i < length; i++) {
        int found = 0;
        
        for (int j = 0; j < length; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'tuple2[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'tuple1[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (tuple1[i] == tuple2[j]) {
                found = 1;
                break;
            }
        }
        
        if (!found) {
            /* Possible weaknesses found:
             *  Cannot determine that 'tuple1[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            result[k][0] = tuple1[i];
            /* Possible weaknesses found:
             *  Cannot determine that 'tuple2[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            result[k][1] = tuple2[i];
            k++;
        }
    }
    
    // Print result tuples
    for (int i = 0; i < k; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'result[i][1]' is initialized [premium-bughuntingUninit]
         *  Cannot determine that 'result[i][0]' is initialized [premium-bughuntingUninit]
         */
        printf("(%d, %d) ", result[i][0], result[i][1]);
    }
}

int main() {
    int tuple1[] = {1, 2, 3, 4, 5};
    int tuple2[] = {4, 5, 6, 7, 8};
    int length = sizeof(tuple1) / sizeof(tuple1[0]);
    
    removeMatchingTuples(tuple1, tuple2, length);

    return 0;
}