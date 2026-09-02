#include <stdio.h>

int sum_negative(int numbers[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        if (numbers[i] < 0) {
            sum += numbers[i];
        }
    }
    return sum;
}

int main(void) {
    int numbers[] = {5, -3, 8, -12, 7, -1, 0};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int result = sum_negative(numbers, size);
    printf("Sum of negative numbers: %d\n", result);
    return 0;
}