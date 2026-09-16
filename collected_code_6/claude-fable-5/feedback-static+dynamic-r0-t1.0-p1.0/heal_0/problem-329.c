#include <stdio.h>
#include <stddef.h>

size_t count_negatives(const int *arr, size_t len)
{
    size_t count = 0;
    size_t i;

    if (arr == NULL) {
        return 0;
    }

    for (i = 0; i < len; i++) {
        if (arr[i] < 0) {
            count++;
        }
    }

    return count;
}

int main(void)
{
    int numbers[] = { 3, -1, 4, -5, 9, -2, 6, 0, -7 };
    size_t len = sizeof(numbers) / sizeof(numbers[0]);
    size_t result;

    result = count_negatives(numbers, len);

    if (printf("Number of negative values: %zu\n", result) < 0) {
        return 1;
    }

    return 0;
}