#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int find_odd_occurrence(const int *array, size_t length, int *result)
{
    int value = 0;

    if (array == NULL || result == NULL || length == 0U) {
        return 0;
    }

    for (size_t i = 0U; i < length; ++i) {
        value ^= array[i];
    }

    *result = value;
    return 1;
}

int main(void)
{
    const int array[] = {4, 3, 4, 3, 4, 5, 5};
    const size_t length = sizeof(array) / sizeof(array[0]);
    int result = 0;

    if (!find_odd_occurrence(array, length, &result)) {
        fputs("Unable to find the odd-occurring element.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}