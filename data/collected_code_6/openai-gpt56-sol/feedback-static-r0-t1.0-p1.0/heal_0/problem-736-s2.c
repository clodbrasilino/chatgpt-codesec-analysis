#include <stdio.h>
#include <stdlib.h>

static size_t left_insertion_point(const int *values, size_t count, int target)
{
    size_t low = 0;
    size_t high = count;

    while (low < high) {
        size_t middle = low + (high - low) / 2;

        if (values[middle] < target) {
            low = middle + 1;
        } else {
            high = middle;
        }
    }

    return low;
}

int main(void)
{
    int values[] = {1, 3, 3, 5, 7, 9};
    const size_t count = sizeof(values) / sizeof(values[0]);
    int target = 0;

    if (printf("Enter a value: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%d", &target) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    size_t index = left_insertion_point(values, count, target);

    if (printf("Left insertion point: %zu\n", index) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}