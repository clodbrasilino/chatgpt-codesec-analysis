#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'ULLONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

unsigned long long find_first_factorial_divisible_by_x(unsigned long long x) {
    if (x == 0) {
        return 0;
    }

    unsigned long long n = 1;
    unsigned long long current_factorial = 1;

    while (current_factorial % x != 0) {
        n++;
        if (n == 0) {
            return 0;
        }
        /* Possible weaknesses found:
         *  each undeclared identifier is reported only once for each function it appears in
         *  use of undeclared identifier 'ULLONG_MAX'
         *  'ULLONG_MAX' undeclared (first use in this function)
         */
        if (current_factorial > ULLONG_MAX / n) {
            return 0;
        }
        current_factorial *= n;
    }

    return n;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr;
    unsigned long long x = strtoull(argv[1], &endptr, 10);

    if (*endptr != '\0') {
        return EXIT_FAILURE;
    }

    unsigned long long result = find_first_factorial_divisible_by_x(x);

    printf("%llu\n", result);

    return EXIT_SUCCESS;
}