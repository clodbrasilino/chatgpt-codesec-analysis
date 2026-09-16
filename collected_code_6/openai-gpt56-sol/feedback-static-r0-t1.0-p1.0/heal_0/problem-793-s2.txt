#include <stdio.h>
#include <stdlib.h>

static int find_last_position(const int *array, size_t length, int target, size_t *position)
{
    size_t left = 0;
    size_t right = length;

    if (array == NULL || position == NULL) {
        return 0;
    }

    while (left < right) {
        size_t middle = left + (right - left) / 2;

        if (array[middle] <= target) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }

    if (left > 0 && array[left - 1] == target) {
        *position = left - 1;
        return 1;
    }

    return 0;
}

int main(void)
{
    size_t length;
    int target;
    int *array = NULL;
    size_t position;

    if (scanf("%zu", &length) != 1) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        return EXIT_FAILURE;
    }

    if (length > 0) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            return EXIT_FAILURE;
        }

        for (size_t i = 0; i < length; ++i) {
            if (scanf("%d", &array[i]) != 1) {
                free(array);
                return EXIT_FAILURE;
            }
        }
    }

    if (scanf("%d", &target) != 1) {
        free(array);
        return EXIT_FAILURE;
    }

    if (find_last_position(array, length, target, &position)) {
        printf("%zu\n", position);
    } else {
        printf("-1\n");
    }

    free(array);
    return EXIT_SUCCESS;
}