#include <stdio.h>
#include <stdlib.h>

int sum_negative_numbers(int *numbers, int size) {
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        if (numbers[i] < 0) {
            sum += numbers[i];
        }
    }
    return sum;
}

int main() {
    int numbers[] = {2, -3, 4, -1, -5, 6, 7, -2};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int result = sum_negative_numbers(numbers, size);
    printf("Sum of negative numbers: %d\n", result);
    return 0;
}