#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

static size_t right_insertion_point(const int *values, size_t count, int target)
{
    size_t left = 0;
    size_t right = count;

    while (left < right) {
        size_t middle = left + (right - left) / 2;

        if (values[middle] <= target) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }

    return left;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *end = NULL;
    long parsed;
    int target;
    const int values[] = {1, 2, 2, 4, 7, 7, 9};
    const size_t count = sizeof(values) / sizeof(values[0]);

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtol(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        /* Possible weaknesses found:
         *  each undeclared identifier is reported only once for each function it appears in
         *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
         *  use of undeclared identifier 'INT_MIN'
         *  use of undeclared identifier 'INT_MAX'
         *  'INT_MIN' undeclared (first use in this function)
         *  'INT_MAX' undeclared (first use in this function)
         */
        parsed < INT_MIN || parsed > INT_MAX) {
        fprintf(stderr, "Invalid integer: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    target = (int)parsed;
    printf("%zu\n", right_insertion_point(values, count, target));

    return EXIT_SUCCESS;
}