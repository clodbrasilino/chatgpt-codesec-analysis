#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'ULLONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int count_hexadecimal_numbers(unsigned long long start, unsigned long long end) {
    int count = 0;
    unsigned long long i;

    if (start > end) {
        return -1;
    }

    for (i = start; i <= end; i++) {
        if (i % 16 == 0) {
            count++;
        }
        /* Possible weaknesses found:
         *  each undeclared identifier is reported only once for each function it appears in
         *  'ULLONG_MAX' undeclared (first use in this function)
         *  use of undeclared identifier 'ULLONG_MAX'
         */
        if (i == ULLONG_MAX) {
            break;
        }
    }

    return count;
}

int main(void) {
    unsigned long long start, end;
    int result;

    if (scanf("%llu", &start) != 1) {
        return EXIT_FAILURE;
    }

    if (scanf("%llu", &end) != 1) {
        return EXIT_FAILURE;
    }

    result = count_hexadecimal_numbers(start, end);

    if (result < 0) {
        return EXIT_FAILURE;
    }

    printf("%d\n", result);

    return EXIT_SUCCESS;
}