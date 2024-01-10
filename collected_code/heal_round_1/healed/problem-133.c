#include <stdio.h>

int calculateSumOfNegativeNumbers(const int numbers[], int length) {
    int sum = 0;
    for (int i = 0; i < length; i++) {
        if (numbers[i] < 0) {
            sum += numbers[i];
        }
    }
    return sum;
}

int main() {
    const int numbers[] = {1, -2, 3, -4, 5, -6};
    int length = sizeof(numbers) / sizeof(numbers[0]);
    int sum = calculateSumOfNegativeNumbers(numbers, length);
    
    printf("Sum of negative numbers: %d\n", sum);
    
    return 0;
}