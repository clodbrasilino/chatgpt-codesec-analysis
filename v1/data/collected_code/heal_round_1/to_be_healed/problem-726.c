#include <stdio.h>

void multiplyAdjacent(int *arr, int size) {
    for (int i = 1; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'arr[i-1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        int product = arr[i] * arr[i - 1];
        printf("%d ", product);
    }
}

int main() {
    int tuple[] = {1, 2, 3, 4, 5};
    int size = sizeof(tuple) / sizeof(tuple[0]);

    multiplyAdjacent(tuple, size);

    return 0;
}