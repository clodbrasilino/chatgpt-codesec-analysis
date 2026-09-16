#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

static int find_smallest_missing(const int array[], size_t size, int *result)
{
    size_t left = 0;
    size_t right = size;

    if (result == NULL || (array == NULL && size != 0)) {
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

    /* Possible weaknesses found:
     *  'INT_MAX' undeclared (first use in this function)
     *  use of undeclared identifier 'INT_MAX'
     *  each undeclared identifier is reported only once for each function it appears in
     */
    if (left > (size_t)INT_MAX) {
        return -1;
    }

    *result = (int)left;
    return 0;
}

int main(void)
{
    const int array[] = {0, 1, 2, 3, 5, 6, 7};
    const size_t size = sizeof(array) / sizeof(array[0]);
    int missing = 0;

    if (find_smallest_missing(array, size, &missing) != 0) {
        fputs("Unable to find the smallest missing element.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%d\n", missing) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}