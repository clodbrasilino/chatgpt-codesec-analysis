#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    const int a = *(const int *)lhs;
    const int b = *(const int *)rhs;

    return (a > b) - (a < b);
}

static int print_duplicates(const int *values, size_t count)
{
    int *sorted;
    size_t i;

    if (values == NULL && count != 0U) {
        return -1;
    }

    if (count < 2U) {
        return 0;
    }

    if (count > SIZE_MAX / sizeof(*sorted)) {
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

    i = 0U;
    while (i < count) {
        size_t j = i + 1U;

        while (j < count && sorted[j] == sorted[i]) {
            ++j;
        }

        if (j - i > 1U) {
            if (printf("%d\n", sorted[i]) < 0) {
                free(sorted);
                return -1;
            }
        }

        i = j;
    }

    free(sorted);
    return 0;
}

int main(void)
{
    int values[] = {4, 2, 7, 2, 9, 4, 4, 1, 7};
    const size_t count = sizeof(values) / sizeof(values[0]);

    errno = 0;
    if (print_duplicates(values, count) != 0) {
        if (errno != 0) {
            perror("print_duplicates");
        } else {
            fputs("Unable to print duplicates\n", stderr);
        }
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        perror("fflush");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}