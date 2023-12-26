#include <stdio.h>

int minProduct(int array[], int n) {
    /* Possible weaknesses found:
     *  Cannot determine that 'array[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *  Cannot determine that 'array[1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int min_prod = array[0] * array[1];

    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'array[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'array[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            int product = array[i] * array[j];
            if (product < min_prod)
                min_prod = product;
        }
    }

    return min_prod;
}

int main() {
    int array[] = {1, 2, 3, 4, 5};
    int size = sizeof(array) / sizeof(array[0]);
    int result = minProduct(array, size);
    printf("Minimum product: %d\n", result);

    return 0;
}