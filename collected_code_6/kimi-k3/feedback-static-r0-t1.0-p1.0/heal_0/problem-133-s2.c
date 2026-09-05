#include <stdio.h>
#include <stdlib.h>

long long sum_negative_numbers(const int *numbers, size_t count) {
    long long sum = 0;
    if (numbers == NULL) {
        return 0;
    }
    for (size_t i = 0; i < count; i++) {
        if (numbers[i] < 0) {
            sum += numbers[i];
        }
    }
    return sum;
}

int main(void) {
    int numbers[] = {5, -3, 8, -7, 0, -2, 10};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    long long result = sum_negative_numbers(numbers, count);
    printf("Sum of negative numbers: %lld\n", result);
    return 0;
}