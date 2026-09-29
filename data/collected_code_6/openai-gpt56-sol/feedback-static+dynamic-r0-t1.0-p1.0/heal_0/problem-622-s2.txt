#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    const int a = *(const int *)lhs;
    const int b = *(const int *)rhs;

    return (a > b) - (a < b);
}

static int find_median(const int a[], const int b[], size_t size, double *median)
{
    size_t i = 0;
    size_t j = 0;
    size_t count = 0;
    int previous = 0;
    int current = 0;

    if (a == NULL || b == NULL || median == NULL || size == 0) {
        return -1;
    }

    while (count <= size) {
        previous = current;

        if (i < size && (j >= size || a[i] <= b[j])) {
            current = a[i++];
        } else {
            current = b[j++];
        }

        ++count;
    }

    *median = (double)previous / 2.0 + (double)current / 2.0;
    return 0;
}

int main(void)
{
    int first[] = {1, 12, 15, 26, 38};
    int second[] = {2, 13, 17, 30, 45};
    const size_t first_size = sizeof(first) / sizeof(first[0]);
    const size_t second_size = sizeof(second) / sizeof(second[0]);
    double median = 0.0;

    if (first_size != second_size || first_size == 0) {
        fputs("Arrays must have the same nonzero size.\n", stderr);
        return EXIT_FAILURE;
    }

    qsort(first, first_size, sizeof(first[0]), compare_ints);
    qsort(second, second_size, sizeof(second[0]), compare_ints);

    if (find_median(first, second, first_size, &median) != 0) {
        fputs("Failed to calculate the median.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Median: %.2f\n", median) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}