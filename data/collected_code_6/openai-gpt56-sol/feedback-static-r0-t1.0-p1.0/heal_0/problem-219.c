#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    const int a = *(const int *)lhs;
    const int b = *(const int *)rhs;

    return (a > b) - (a < b);
}

static int extract_min_max_k(const int *tuple, size_t length, size_t k,
                             int *minimum, int *maximum)
{
    int *sorted = NULL;

    if (tuple == NULL || minimum == NULL || maximum == NULL ||
        k == 0U || k > length || length > SIZE_MAX / sizeof(*sorted)) {
        return -1;
    }

    sorted = malloc(length * sizeof(*sorted));
    if (sorted == NULL) {
        return -1;
    }

    for (size_t i = 0U; i < length; ++i) {
        sorted[i] = tuple[i];
    }

    qsort(sorted, length, sizeof(*sorted), compare_ints);

    for (size_t i = 0U; i < k; ++i) {
        minimum[i] = sorted[i];
        maximum[i] = sorted[length - k + i];
    }

    free(sorted);
    return 0;
}

static void print_elements(const char *label, const int *elements, size_t count)
{
    printf("%s", label);

    for (size_t i = 0U; i < count; ++i) {
        printf("%s%d", i == 0U ? "" : " ", elements[i]);
    }

    putchar('\n');
}

int main(void)
{
    const int tuple[] = {12, 3, 5, 7, 19, -2, 8, 15};
    const size_t length = sizeof(tuple) / sizeof(tuple[0]);
    const size_t k = 3U;
    int *minimum = NULL;
    int *maximum = NULL;
    int status = EXIT_FAILURE;

    if (k == 0U || k > length || k > SIZE_MAX / sizeof(*minimum)) {
        fputs("Invalid value of k\n", stderr);
        return EXIT_FAILURE;
    }

    minimum = malloc(k * sizeof(*minimum));
    maximum = malloc(k * sizeof(*maximum));

    if (minimum == NULL || maximum == NULL) {
        fputs("Memory allocation failed\n", stderr);
        goto cleanup;
    }

    if (extract_min_max_k(tuple, length, k, minimum, maximum) != 0) {
        fputs("Element extraction failed\n", stderr);
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