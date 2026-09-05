#include <stdio.h>
#include <stdlib.h>

int sum_negative_numbers(const int *array, size_t size) {
    if (array == NULL) {
        return 0;
    }

    int sum = 0;
    for (size_t i = 0; i < size; i++) {
        if (array[i] < 0) {
            sum += array[i];
        }
    }
    return sum;
}

int main(void) {
    int numbers[] = {5, -2, 14, -7, 0, -3, 8};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);

    int result = sum_negative_numbers(numbers, count);

    printf("%d\n", result);

    return 0;
}