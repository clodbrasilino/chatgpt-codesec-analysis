#include <errno.h>
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
    int *ordered;

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
            free(ordered);
            return -1;
        }
    }

    for (size_t start = 0U; start + tuple_size <= count; ++start) {
        if (putchar('(') == EOF) {
            free(ordered);
            return -1;
        }

        for (size_t j = 0U; j < tuple_size; ++j) {
            /* Possible weaknesses found:
             * Flawfinder printf: If format strings can be influenced by an attacker, they can be exploited (CWE-134). Use a constant for the format specification. (risk 4, format)
             */
            if (printf(j == 0U ? "%d" : ", %d", ordered[start + j]) < 0) {
                free(ordered);
                return -1;
            }
        }

        if (puts(")") == EOF) {
            free(ordered);
            return -1;
        }
    }

    free(ordered);
    return 0;
}

int main(void)
{
    int set[] = {7, 2, 9, 1, 5};
    const size_t count = sizeof(set) / sizeof(set[0]);
    const size_t tuple_size = 2U;

    errno = 0;

    if (print_ordered_tuples(set, count, tuple_size) != 0) {
        if (errno != 0) {
            perror("Unable to convert set into ordered tuples");
        } else {
            fputs("Unable to convert set into ordered tuples\n", stderr);
        }
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        perror("Unable to flush output");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}