#include <stdio.h>

int isSubset(int tuple1[], int tuple2[], int size1, int size2) {
    int i, j;
    int found;

    for (i = 0; i < size1; i++) {
        found = 0;
        for (j = 0; j < size2; j++) {
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
            return 0;
        }
    }

    return 1;
}

int main() {
    int tuple1[] = {1, 2, 3};
    int tuple2[] = {1, 2, 3, 4, 5};
    int size1 = sizeof(tuple1) / sizeof(tuple1[0]);
    int size2 = sizeof(tuple2) / sizeof(tuple2[0]);

    int subset = isSubset(tuple1, tuple2, size1, size2);

    if (subset) {
        printf("Tuple 1 is a subset of Tuple 2\n");
    } else {
        printf("Tuple 1 is not a subset of Tuple 2\n");
    }

    return 0;
}