#include <stdio.h>

void pairwiseAddition(int tuple1[], int tuple2[], int length) {
    int result[length];
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    for (int i = 0; i < length; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'tuple2[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'tuple1[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        result[i] = tuple1[i] + tuple2[i];
    }
    printf("Pairwise Addition: (");
    for (int i = 0; i < length - 1; i++) {
        printf("%d, ", result[i]);
    }
    printf("%d)\n", result[length - 1]);
}

int main() {
    int tuple1[] = {1, 2, 3};
    int tuple2[] = {4, 5, 6};
    int length = sizeof(tuple1) / sizeof(tuple1[0]);
    pairwiseAddition(tuple1, tuple2, length);
    return 0;
}