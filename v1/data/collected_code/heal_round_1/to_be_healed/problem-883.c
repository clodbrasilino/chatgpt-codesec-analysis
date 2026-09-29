#include <stdio.h>

// Function to find numbers divisible by m and n
void findDivisibleNumbers(int list[], int size, int m, int n) {
    printf("Numbers divisible by %d and %d: ", m, n);
    
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (list[i] % m == 0 && list[i] % n == 0) {
            /* Possible weaknesses found:
             *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            printf("%d ", list[i]);
        }
    }
    
    printf("\n");
}

int main() {
    int numbers[] = {2, 4, 6, 8, 9, 12, 15, 18};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int m = 3, n = 4;
    
    findDivisibleNumbers(numbers, size, m, n);
    
    return 0;
}