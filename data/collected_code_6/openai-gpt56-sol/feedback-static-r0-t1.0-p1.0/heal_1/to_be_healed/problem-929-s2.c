#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static size_t count_repeated_items(const int *tuple, size_t length)
{
    size_t repeated = 0;
    size_t run_length = 1;

    if (tuple == NULL || length < 2) {
        return 0;
    }

    for (size_t i = 1; i < length; ++i) {
        if (tuple[i] == tuple[i - 1]) {
            ++run_length;
        } else {
            if (run_length > 1) {
                repeated += run_length;
            }
            run_length = 1;
        }
    }

    if (run_length > 1) {
        repeated += run_length;
    }

    return repeated;
}

int main(int argc, char **argv)
{
    int *tuple = NULL;
    size_t length;
    char *end = NULL;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s integer [integer ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    length = (size_t)(argc - 1);

    if (length > SIZE_MAX / sizeof(*tuple)) {
        fprintf(stderr, "Input is too large\n");
        return EXIT_FAILURE;
    }

    tuple = malloc(length * sizeof(*tuple));
    if (tuple == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        long value;

        errno = 0;
        end = NULL;
        value = strtol(argv[i + 1], &end, 10);

        if (errno == ERANGE || end == argv[i + 1] || *end != '\0' ||
            /* Possible weaknesses found:
             *  each undeclared identifier is reported only once for each function it appears in
             *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
             *  use of undeclared identifier 'INT_MIN'
             *  use of undeclared identifier 'INT_MAX'
             *  'INT_MIN' undeclared (first use in this function)
             *  'INT_MAX' undeclared (first use in this function)
             */
            value < INT_MIN || value > INT_MAX) {
            fprintf(stderr, "Invalid integer: %s\n", argv[i + 1]);
            free(tuple);
            return EXIT_FAILURE;
        }

        tuple[i] = (int)value;
    }

    qsort(tuple, length, sizeof(*tuple), compare_ints);
    printf("%zu\n", count_repeated_items(tuple, length));

    free(tuple);
    return EXIT_SUCCESS;
}