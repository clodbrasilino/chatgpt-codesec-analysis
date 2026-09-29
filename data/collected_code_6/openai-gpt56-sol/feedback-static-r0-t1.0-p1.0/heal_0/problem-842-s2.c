#include <stdio.h>
#include <stdlib.h>

static int find_odd_occurrence(const int *array, size_t length, int *result)
{
    if (array == NULL || result == NULL || length == 0U) {
        return 0;
    }

    int value = 0;

    for (size_t i = 0U; i < length; ++i) {
        value ^= array[i];
    }

    *result = value;
    return 1;
}

int main(void)
{
    size_t length = 0U;

    if (scanf("%zu", &length) != 1 || length == 0U ||
        length > SIZE_MAX / sizeof(int)) {
        return EXIT_FAILURE;
    }

    int *array = malloc(length * sizeof(*array));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    int result = 0;
    if (!find_odd_occurrence(array, length, &result)) {
        free(array);
        return EXIT_FAILURE;
    }

    printf("%d\n", result);
    free(array);

    return EXIT_SUCCESS;
}