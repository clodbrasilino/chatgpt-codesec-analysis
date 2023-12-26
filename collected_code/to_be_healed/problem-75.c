#include <stdio.h>

void findDivisibleTuples(int n, int k, int tuples[][2]) {
    printf("Divisible tuples:\n");
    for (int i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'tuples[i][1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'tuples[i][0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (tuples[i][0] % k == 0 && tuples[i][1] % k == 0) {
            /* Possible weaknesses found:
             *  Cannot determine that 'tuples[i][1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'tuples[i][0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            printf("(%d, %d)\n", tuples[i][0], tuples[i][1]);
        }
    }
}

int main() {
    int n = 4; // Number of tuples
    int k = 3; // Divisor

    /* Possible weaknesses found:
     *  variable-sized object may not be initialized except with an empty initializer
     */
    int tuples[n][2] = {{1, 6}, {9, -3}, {4, 8}, {10, 12}};

    findDivisibleTuples(n, k, tuples);

    return 0;
}