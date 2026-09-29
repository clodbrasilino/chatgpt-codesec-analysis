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
    int values[] = {1, 3, 3, 5, 8, 13};
    const size_t count = sizeof(values) / sizeof(values[0]);
    int target = 3;
    size_t position = left_insertion_point(values, count, target);

    if (printf("%zu\n", position) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}