#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static size_t left_insertion_point(const int *values, size_t count, int target)
{
    size_t left = 0;
    size_t right = count;

    while (left < right) {
        size_t middle = left + (right - left) / 2;

        if (values[middle] < target) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }

    return left;
}

int main(void)
{
    const int values[] = {1, 2, 2, 4, 7, 9};
    const size_t count = sizeof(values) / sizeof(values[0]);
    int target;

    if (printf("Enter a value: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%d", &target) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    size_t position = left_insertion_point(values, count, target);

    if (printf("Left insertion point: %zu\n", position) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}