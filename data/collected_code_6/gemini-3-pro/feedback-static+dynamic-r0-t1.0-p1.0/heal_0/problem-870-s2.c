#include <stdio.h>
#include <stdlib.h>

int sum_positive_numbers(const int *numbers, size_t length) {
    if (numbers == NULL) {
        return 0;
    }

    int sum = 0;
    for (size_t i = 0; i < length; i++) {
        if (numbers[i] > 0) {
            sum += numbers[i];
        }
    }
    return sum;
}

int main(void) {
    int my_numbers[] = {-1, 5, -3, 10, 2, 0, -8};
    size_t length = sizeof(my_numbers) / sizeof(my_numbers[0]);

    int result = sum_positive_numbers(my_numbers, length);

    printf("Sum of positive numbers: %d\n", result);

    return 0;
}