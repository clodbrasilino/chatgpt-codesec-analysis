#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

static int find_smallest_missing(const int array[], size_t length, int *result)
{
    size_t left = 0;
    size_t right = length;

    if (result == NULL || (array == NULL && length != 0)) {
        return -1;
    }

    while (left < right) {
        size_t middle = left + (right - left) / 2;

        if (array[middle] == (int)middle) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }

    *result = (int)left;
    return 0;
}

int main(void)
{
    const int array[] = {0, 1, 2, 3, 5, 6, 7};
    const size_t length = sizeof(array) / sizeof(array[0]);
    int missing = 0;

    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  'INT_MAX' undeclared (first use in this function)
     *  use of undeclared identifier 'INT_MAX'
     */
    if (length > (size_t)INT_MAX) {
        return EXIT_FAILURE;
    }

    if (find_smallest_missing(array, length, &missing) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%d\n", missing) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}