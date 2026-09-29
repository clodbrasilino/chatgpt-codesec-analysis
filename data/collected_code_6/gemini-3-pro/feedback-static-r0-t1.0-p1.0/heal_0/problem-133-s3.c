#include <stdio.h>
#include <stdlib.h>

int sum_of_negatives(const int *list, size_t size) {
    if (list == NULL || size == 0) {
        return 0;
    }

    int sum = 0;
    for (size_t i = 0; i < size; ++i) {
        if (list[i] < 0) {
            sum += list[i];
        }
    }

    return sum;
}

int main(void) {
    int numbers[] = {1, -2, 3, -4, 5, -6, 7};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);

    int result = sum_of_negatives(numbers, size);

    printf("Sum of negative numbers: %d\n", result);

    return 0;
}