#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int find_kth_element(const int *array, size_t length, size_t k, int *result)
{
    if (array == NULL || result == NULL || k == 0 || k > length) {
        return -1;
    }

    *result = array[k - 1];
    return 0;
}

int main(void)
{
    int *array = NULL;
    int result = 0;
    size_t length = 0;
    size_t k = 0;
    size_t i = 0;

    if (scanf("%zu", &length) != 1 || length == 0 ||
        length > SIZE_MAX / sizeof(*array)) {
        fputs("Invalid array length\n", stderr);
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            fputs("Invalid array element\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (scanf("%zu", &k) != 1) {
        fputs("Invalid position\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    if (find_kth_element(array, length, k, &result) != 0) {
        fputs("Position out of range\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    printf("%d\n", result);
    free(array);
    return EXIT_SUCCESS;
}