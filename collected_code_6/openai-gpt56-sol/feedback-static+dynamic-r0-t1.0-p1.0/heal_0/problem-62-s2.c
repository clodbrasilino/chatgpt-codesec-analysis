#include <stdio.h>
#include <stdlib.h>

static int find_smallest(const int *values, size_t count, int *smallest)
{
    size_t i;

    if (values == NULL || smallest == NULL || count == 0U) {
        return -1;
    }

    *smallest = values[0];

    for (i = 1U; i < count; ++i) {
        if (values[i] < *smallest) {
            *smallest = values[i];
        }
    }

    return 0;
}

int main(void)
{
    int values[] = {42, -7, 19, 0, 5};
    const size_t count = sizeof(values) / sizeof(values[0]);
    int smallest;

    if (find_smallest(values, count, &smallest) != 0) {
        (void)fprintf(stderr, "Unable to find the smallest value.\n");
        return EXIT_FAILURE;
    }

    if (printf("%d\n", smallest) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}