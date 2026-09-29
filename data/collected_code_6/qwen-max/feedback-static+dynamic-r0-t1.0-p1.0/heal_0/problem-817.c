#include <stdio.h>
#include <stdbool.h>

bool is_divisible(int number, int m, int n) {
    return (number % m == 0) || (number % n == 0);
}

void find_divisible(int *numbers, int size, int m, int n) {
    for (int i = 0; i < size; i++) {
        if (is_divisible(numbers[i], m, n)) {
            printf("%d\n", numbers[i]);
        }
    }
}

int main() {
    int numbers[] = {10, 20, 33, 40, 55};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int m = 5;
    int n = 11;
    find_divisible(numbers, size, m, n);
    return 0;
}