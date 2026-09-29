#include <stdio.h>

int findEven(int *numbers, int size) {
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'numbers[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (numbers[i] % 2 == 0) {
            /* Possible weaknesses found:
             *  Cannot determine that 'numbers[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            return numbers[i];
        }
    }
    return -1; // No even number found
}

int main() {
    int numbers[] = {1, 3, 5, 2, 4, 6, 7, 9, 10};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    int firstEven = findEven(numbers, size);
    printf("First even number: %d\n", firstEven);

    return 0;
}