#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static int compare_ascending(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static int extract_min_max_k(const int *values, size_t count, size_t k,
                             int *minimum, int *maximum)
{
    int *sorted;
    size_t i;

    if (values == NULL || minimum == NULL || maximum == NULL ||
        count == 0 || k == 0 || k > count ||
        count > SIZE_MAX / sizeof(*sorted)) {
        return -1;
    }

    sorted = malloc(count * sizeof(*sorted));
    if (sorted == NULL) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        sorted[i] = values[i];
    }

    qsort(sorted, count, sizeof(*sorted), compare_ascending);

    for (i = 0; i < k; ++i) {
        minimum[i] = sorted[i];
        maximum[i] = sorted[count - 1U - i];
    }

    free(sorted);
    return 0;
}

static void print_elements(const char *label, const int *values, size_t count)
{
    size_t i;

    printf("%s", label);
    for (i = 0; i < count; ++i) {
        printf("%s%d", i == 0 ? "" : " ", values[i]);
    }
    putchar('\n');
}

int main(void)
{
    const int tuple[] = {12, 3, 5, 7, 19, 1, 8, 14};
    const size_t count = sizeof(tuple) / sizeof(tuple[0]);
    const size_t k = 3;
    int *minimum;
    int *maximum;
    int status = EXIT_FAILURE;

    if (k == 0 || k > count || k > SIZE_MAX / sizeof(*minimum)) {
        fputs("Invalid value of k\n", stderr);
        return EXIT_FAILURE;
    }

    minimum = malloc(k * sizeof(*minimum));
    maximum = malloc(k * sizeof(*maximum));

    if (minimum == NULL || maximum == NULL) {
        fputs("Memory allocation failed\n", stderr);
        goto cleanup;
    }

    if (extract_min_max_k(tuple, count, k, minimum, maximum) != 0) {
        fputs("Unable to extract elements\n", stderr);
        goto cleanup;
    }

    print_elements("Minimum elements: ", minimum, k);
    print_elements("Maximum elements: ", maximum, k);
    status = EXIT_SUCCESS;

cleanup:
    free(maximum);
    free(minimum);
    return status;
}