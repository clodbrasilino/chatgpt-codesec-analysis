#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    const int a = *(const int *)lhs;
    const int b = *(const int *)rhs;

    return (a > b) - (a < b);
}

static int print_ordered_tuples(const int *set, size_t count, size_t tuple_size)
{
    int *ordered = NULL;
    int result = -1;

    if (set == NULL || count == 0U || tuple_size == 0U || tuple_size > count) {
        return -1;
    }

    if (count > SIZE_MAX / sizeof(*ordered)) {
        return -1;
    }

    ordered = malloc(count * sizeof(*ordered));
    if (ordered == NULL) {
        return -1;
    }

    for (size_t i = 0U; i < count; ++i) {
        ordered[i] = set[i];
    }

    qsort(ordered, count, sizeof(*ordered), compare_ints);

    for (size_t i = 1U; i < count; ++i) {
        if (ordered[i] == ordered[i - 1U]) {
            goto cleanup;
        }
    }

    for (size_t start = 0U; start <= count - tuple_size; ++start) {
        if (putchar('(') == EOF) {
            goto cleanup;
        }

        for (size_t j = 0U; j < tuple_size; ++j) {
            if (j != 0U && fputs(", ", stdout) == EOF) {
                goto cleanup;
            }

            if (printf("%d", ordered[start + j]) < 0) {
                goto cleanup;
            }
        }

        if (puts(")") == EOF) {
            goto cleanup;
        }
    }

    result = 0;

cleanup:
    free(ordered);
    return result;
}

int main(void)
{
    const int set[] = {7, 2, 9, 1, 5};
    const size_t count = sizeof(set) / sizeof(set[0]);
    const size_t tuple_size = 2U;

    if (print_ordered_tuples(set, count, tuple_size) != 0) {
        fputs("Unable to convert set into ordered tuples\n", stderr);
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        fputs("Unable to flush output\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}