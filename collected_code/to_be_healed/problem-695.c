#include <stdio.h>

int checkTuples(int tuple1[], int tuple2[], int length) {
    for (int i = 0; i < length; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'tuple2[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'tuple1[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (tuple2[i] <= tuple1[i]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int tuple1[] = {1, 2, 3};
    int tuple2[] = {3, 4, 5};
    int length = sizeof(tuple1) / sizeof(tuple1[0]);

    if (checkTuples(tuple1, tuple2, length)) {
        printf("Each element of the second tuple is greater than its corresponding index in the first tuple\n");
    } else {
        printf("At least one element of the second tuple is less than or equal to its corresponding index in the first tuple\n");
    }
    
    return 0;
}