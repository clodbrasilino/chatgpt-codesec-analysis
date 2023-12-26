#include <stdio.h>

void printPositiveNumbers(int* numbers, int length) {
    for (int i = 0; i < length; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'numbers[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (numbers[i] > 0) {
            /* Possible weaknesses found:
             *  Cannot determine that 'numbers[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            printf("%d\n", numbers[i]);
        }
    }
}

int main() {
    int numbers[] = {-1, 5, -3, 10, -7};
    int length = sizeof(numbers) / sizeof(numbers[0]);

    printPositiveNumbers(numbers, length);
    
    return 0;
}