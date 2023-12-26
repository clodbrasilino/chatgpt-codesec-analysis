#include <stdio.h>

int findProduct(int numbers[], int length) {
    int even = -1, odd = -1;
    int product = 0;

    for (int i = 0; i < length; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'numbers[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (numbers[i] % 2 == 0 && even == -1) {
            /* Possible weaknesses found:
             *  Cannot determine that 'numbers[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            even = numbers[i];
        /* Possible weaknesses found:
         *  Cannot determine that 'numbers[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        } else if (numbers[i] % 2 != 0 && odd == -1) {
            /* Possible weaknesses found:
             *  Cannot determine that 'numbers[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            odd = numbers[i];
        }

        if (even != -1 && odd != -1) {
            product = even * odd;
            break;
        }
    }

    return product;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int length = sizeof(numbers) / sizeof(numbers[0]);
    
    int result = findProduct(numbers, length);
    printf("Product: %d\n", result);

    return 0;
}