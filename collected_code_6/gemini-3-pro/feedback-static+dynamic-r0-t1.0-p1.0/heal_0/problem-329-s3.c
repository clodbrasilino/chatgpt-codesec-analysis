#include <stdio.h>
#include <stddef.h>

size_t count_negative_numbers(const int *array, size_t size) {
    size_t count = 0;

    if (array == NULL || size == 0) {
        return 0;
    }

    for (size_t i = 0; i < size; ++i) {
        if (array[i] < 0) {
            count++;
        }
    }

    return count;
}

int main(void) {
    int numbers[] = { 10, -2, 0, -4, 5, -99, 3, -1 };
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    size_t negative_count = 0;

    negative_count = count_negative_numbers(numbers, size);

    printf("%zu\n", negative_count);

    return 0;
}