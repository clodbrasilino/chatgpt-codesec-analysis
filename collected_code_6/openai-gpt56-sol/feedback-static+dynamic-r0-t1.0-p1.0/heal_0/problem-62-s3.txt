#include <stdio.h>
#include <stdlib.h>

static int find_smallest(const int values[], size_t count, int *smallest)
{
    if (values == NULL || smallest == NULL || count == 0U) {
        return -1;
    }

    *smallest = values[0];

    for (size_t i = 1U; i < count; ++i) {
        if (values[i] < *smallest) {
            *smallest = values[i];
        }
    }

    return 0;
}

int main(void)
{
    const int values[] = {42, -7, 19, 0, 8, -3};
    const size_t count = sizeof(values) / sizeof(values[0]);
    int smallest = 0;

    if (find_smallest(values, count, &smallest) != 0) {
        fputs("Unable to find the smallest number.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Smallest number: %d\n", smallest) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}