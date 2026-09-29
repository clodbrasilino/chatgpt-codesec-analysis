#include <stdio.h>

int calculateProduct(int *tuple, int size) {
    int product = 1;
    
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'tuple[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        product *= tuple[i];
    }
    
    return product;
}

int main() {
    int tuple[] = {2, 3, 4, 5};
    int size = sizeof(tuple) / sizeof(tuple[0]);

    int result = calculateProduct(tuple, size);

    printf("Product: %d\n", result);

    return 0;
}