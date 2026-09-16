#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static int first_missing_positive(int *numbers, size_t length, int *result)
{
    if (result == NULL || (numbers == NULL && length != 0U)) {
        return -1;
    }

    for (size_t i = 0U; i < length; ++i) {
        while (numbers[i] > 0 && (size_t)numbers[i] <= length) {
            size_t target = (size_t)numbers[i] - 1U;

            if (numbers[target] == numbers[i]) {
                break;
            }

            int temporary = numbers[i];
            numbers[i] = numbers[target];
            numbers[target] = temporary;
        }
    }

    for (size_t i = 0U; i < length; ++i) {
        if (numbers[i] <= 0 || (size_t)numbers[i] != i + 1U) {
            if (i >= (size_t)INT_MAX) {
                return -1;
            }
            *result = (int)(i + 1U);
            return 0;
        }
    }

    if (length >= (size_t)INT_MAX) {
        return -1;
    }

    *result = (int)(length + 1U);
    return 0;
}

int main(void)
{
    int numbers[] = {3, 4, -1, 1};
    const size_t length = sizeof(numbers) / sizeof(numbers[0]);
    int result = 0;

    if (first_missing_positive(numbers, length, &result) != 0) {
        fputs("Unable to determine the first missing positive number.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}