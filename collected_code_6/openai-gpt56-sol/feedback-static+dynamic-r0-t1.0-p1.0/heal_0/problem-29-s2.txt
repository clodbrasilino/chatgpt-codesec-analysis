#include <stdio.h>
#include <stdlib.h>

static int find_odd_occurrence(const int *array, size_t length, int *result)
{
    size_t i;
    int value = 0;

    if (array == NULL || result == NULL || length == 0U) {
        return -1;
    }

    for (i = 0U; i < length; ++i) {
        value ^= array[i];
    }

    *result = value;
    return 0;
}

int main(void)
{
    int numbers[] = {4, 3, 4, 3, 4, 5, 5};
    const size_t count = sizeof(numbers) / sizeof(numbers[0]);
    int result;

    if (find_odd_occurrence(numbers, count, &result) != 0) {
        fputs("Unable to find the odd-occurring element.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}