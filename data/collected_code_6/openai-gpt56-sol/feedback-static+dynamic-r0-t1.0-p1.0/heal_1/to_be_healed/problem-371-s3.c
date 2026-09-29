#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

static int find_smallest_missing(const int array[], size_t length, int *result)
{
    if (result == NULL || (array == NULL && length > 0U)) {
        return -1;
    }

    int expected = 0;

    for (size_t i = 0U; i < length; ++i) {
        if (array[i] < expected) {
            continue;
        }

        if (array[i] > expected) {
            break;
        }

        /* Possible weaknesses found:
         *  'INT_MAX' undeclared (first use in this function)
         *  use of undeclared identifier 'INT_MAX'
         *  each undeclared identifier is reported only once for each function it appears in
         */
        if (expected == INT_MAX) {
            return -1;
        }

        ++expected;
    }

    *result = expected;
    return 0;
}

int main(void)
{
    const int array[] = {0, 1, 2, 4, 5, 6};
    const size_t length = sizeof(array) / sizeof(array[0]);
    int missing = 0;

    if (find_smallest_missing(array, length, &missing) != 0) {
        fputs("Unable to find the smallest missing element.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%d\n", missing);
    return EXIT_SUCCESS;
}