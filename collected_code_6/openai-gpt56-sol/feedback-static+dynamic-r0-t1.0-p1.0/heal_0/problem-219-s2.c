#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static int extract_min_max_k(const int *values, size_t count, size_t k,
                             int *minimums, int *maximums)
{
    int *sorted;
    size_t i;

    if (values == NULL || minimums == NULL || maximums == NULL ||
        count == 0U || k == 0U || k > count ||
        count > SIZE_MAX / sizeof(*sorted)) {
        return -1;
    }

    sorted = malloc(count * sizeof(*sorted));
    if (sorted == NULL) {
        return -1;
    }

    for (i = 0U; i < count; ++i) {
        sorted[i] = values[i];
    }

    qsort(sorted, count, sizeof(*sorted), compare_ints);

    for (i = 0U; i < k; ++i) {
        minimums[i] = sorted[i];
        maximums[i] = sorted[count - k + i];
    }

    free(sorted);
    return 0;
}

static void print_elements(const int *values, size_t count)
{
    size_t i;

    for (i = 0U; i < count; ++i) {
        if (i != 0U) {
            printf(" ");
        }
        printf("%d", values[i]);
    }
    printf("\n");
}

int main(void)
{
    const int tuple[] = {12, 3, 7, 1, 19, 5, 8, 15};
    const size_t count = sizeof(tuple) / sizeof(tuple[0]);
    const size_t k = 3U;
    int *minimums;
    int *maximums;
    int status = EXIT_FAILURE;

    if (k == 0U || k > count || k > SIZE_MAX / sizeof(*minimums)) {
        return EXIT_FAILURE;
    }

    minimums = malloc(k * sizeof(*minimums));
    if (minimums == NULL) {
        return EXIT_FAILURE;
    }

    maximums = malloc(k * sizeof(*maximums));
    if (maximums == NULL) {
        free(minimums);
        return EXIT_FAILURE;
    }

    if (extract_min_max_k(tuple, count, k, minimums, maximums) == 0) {
        printf("Minimum %zu elements: ", k);
        print_elements(minimums, k);
        printf("Maximum %zu elements: ", k);
        print_elements(maximums, k);
        status = EXIT_SUCCESS;
    }

    free(maximums);
    free(minimums);

    return status;
}