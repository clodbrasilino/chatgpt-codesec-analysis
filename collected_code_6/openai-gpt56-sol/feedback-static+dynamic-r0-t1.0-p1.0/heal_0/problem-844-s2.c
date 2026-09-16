#include <stdio.h>
#include <stdlib.h>

static int find_kth_odd_even(const int *array, size_t length, size_t k, int *result)
{
    if (array == NULL || result == NULL || k == 0 || k > length) {
        return 0;
    }

    size_t position = 0;

    for (size_t i = 0; i < length; ++i) {
        if (array[i] % 2 != 0 && ++position == k) {
            *result = array[i];
            return 1;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (array[i] % 2 == 0 && ++position == k) {
            *result = array[i];
            return 1;
        }
    }

    return 0;
}

int main(void)
{
    size_t length;
    size_t k;

    if (scanf("%zu", &length) != 1 || length == 0 ||
        length > SIZE_MAX / sizeof(int)) {
        return EXIT_FAILURE;
    }

    int *array = malloc(length * sizeof(*array));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (scanf("%zu", &k) != 1) {
        free(array);
        return EXIT_FAILURE;
    }

    int result;
    if (!find_kth_odd_even(array, length, k, &result)) {
        free(array);
        return EXIT_FAILURE;
    }

    printf("%d\n", result);
    free(array);
    return EXIT_SUCCESS;
}