#include <stdio.h>

void findDivisibleNumbers(const int list[], int size, int m, int n) {
    printf("Numbers divisible by %d and %d: ", m, n);
    
    for (int i = 0; i < size; i++) {
        if (list[i] % m == 0 && list[i] % n == 0) {
            printf("%d ", list[i]);
        }
    }
    printf("\n");
}

int main() {
    const int numbers[] = {2, 4, 6, 8, 9, 12, 15, 18};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int m = 3, n = 4;
    
    findDivisibleNumbers(numbers, size, m, n);
    
    return 0;
}