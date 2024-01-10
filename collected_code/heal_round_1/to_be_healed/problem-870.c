#include <stdio.h>

int calculateSumOfPositives(int numbers[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'numbers[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (numbers[i] > 0) {
            /* Possible weaknesses found:
             *  Cannot determine that 'numbers[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            sum += numbers[i];
        }
    }
    return sum;
}

int main() {
    int numbers[] = {2, -4, 6, -8, 10};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    int sum = calculateSumOfPositives(numbers, size);
    
    printf("Sum of positive numbers: %d\n", sum);
    
    return 0;
}