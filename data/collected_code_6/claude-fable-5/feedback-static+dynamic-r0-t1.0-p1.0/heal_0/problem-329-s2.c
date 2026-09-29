#include <stdio.h>
#include <stddef.h>

size_t count_negatives(const int *arr, size_t len)
{
    size_t count = 0;

    if (arr == NULL) {
        return 0;
    }

    for (size_t i = 0; i < len; i++) {
        if (arr[i] < 0) {
            count++;
        }
    }

    return count;
}

int main(void)
{
    int numbers[] = { 3, -1, -7, 0, 12, -5, 8, -2 };
    size_t len = sizeof(numbers) / sizeof(numbers[0]);
    size_t result = count_negatives(numbers, len);

    if (printf("Number of negative values: %zu\n", result) < 0) {
        return 1;
    }

    return 0;
}