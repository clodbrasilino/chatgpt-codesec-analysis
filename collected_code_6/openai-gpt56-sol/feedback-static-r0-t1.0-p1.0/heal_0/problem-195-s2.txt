#include <stdio.h>
#include <stdlib.h>

static int find_first_position(const int *array, size_t length, int target, size_t *position)
{
    if (array == NULL || position == NULL || length == 0U) {
        return 0;
    }

    size_t left = 0U;
    size_t right = length;

    while (left < right) {
        size_t middle = left + (right - left) / 2U;

        if (array[middle] < target) {
            left = middle + 1U;
        } else {
            right = middle;
        }
    }

    if (left < length && array[left] == target) {
        *position = left;
        return 1;
    }

    return 0;
}

int main(void)
{
    size_t length = 0U;
    int target = 0;

    if (scanf("%zu", &length) != 1 || length == 0U) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(int)) {
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

        if (i > 0U && array[i] < array[i - 1U]) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (scanf("%d", &target) != 1) {
        free(array);
        return EXIT_FAILURE;
    }

    size_t position = 0U;

    if (find_first_position(array, length, target, &position)) {
        printf("%zu\n", position);
    } else {
        printf("-1\n");
    }

    free(array);
    return EXIT_SUCCESS;
}