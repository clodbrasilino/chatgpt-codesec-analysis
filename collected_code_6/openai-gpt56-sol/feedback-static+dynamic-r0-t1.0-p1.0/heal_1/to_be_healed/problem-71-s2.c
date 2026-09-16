#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

static void comb_sort(int *array, size_t length)
{
    size_t gap = length;
    int swapped = 1;

    while (gap > 1U || swapped != 0) {
        size_t i;

        gap = (gap * 10U) / 13U;
        if (gap < 1U) {
            gap = 1U;
        }

        swapped = 0;

        for (i = 0U; i + gap < length; ++i) {
            if (array[i] > array[i + gap]) {
                const int temporary = array[i];

                array[i] = array[i + gap];
                array[i + gap] = temporary;
                swapped = 1;
            }
        }
    }
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    int *values;
    size_t count;
    size_t i;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s integer [integer ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    count = (size_t)(argc - 1);

    if (count > SIZE_MAX / sizeof(*values)) {
        fprintf(stderr, "Input is too large\n");
        return EXIT_FAILURE;
    }

    values = malloc(count * sizeof(*values));
    if (values == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; ++i) {
        char *end;
        long parsed;

        errno = 0;
        end = NULL;
        parsed = strtol(argv[i + 1U], &end, 10);

        if (errno == ERANGE || end == argv[i + 1U] || *end != '\0' ||
            /* Possible weaknesses found:
             *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
             *  use of undeclared identifier 'INT_MIN'
             *  'INT_MAX' undeclared (first use in this function)
             *  use of undeclared identifier 'INT_MAX'
             *  'INT_MIN' undeclared (first use in this function)
             *  each undeclared identifier is reported only once for each function it appears in
             */
            parsed < INT_MIN || parsed > INT_MAX) {
            fprintf(stderr, "Invalid integer: %s\n", argv[i + 1U]);
            free(values);
            return EXIT_FAILURE;
        }

        values[i] = (int)parsed;
    }

    comb_sort(values, count);

    for (i = 0U; i < count; ++i) {
        if (printf("%s%d", i == 0U ? "" : " ", values[i]) < 0) {
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}