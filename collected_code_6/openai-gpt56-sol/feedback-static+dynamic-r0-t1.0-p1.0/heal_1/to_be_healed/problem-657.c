#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'LDBL_MAX' is defined in header '<float.h>'; this is probably fixable by adding '#include <float.h>'
  */

static int first_factorial_digit(unsigned long long number)
{
    if (number < 2U) {
        return 1;
    }

    long double logarithm = lgammal((long double)number + 1.0L) / logl(10.0L);

    if (!isfinite(logarithm)) {
        return -1;
    }

    long double fractional_part = logarithm - floorl(logarithm);
    long double leading_value = powl(10.0L, fractional_part);

    if (!isfinite(leading_value)) {
        return -1;
    }

    int digit = (int)floorl(leading_value + 1e-12L);
    return digit > 9 ? 9 : digit;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nonnegative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    unsigned long long number = strtoull(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' || argv[1][0] == '-') {
        fprintf(stderr, "Invalid nonnegative integer\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  use of undeclared identifier 'LDBL_MAX'
     *  each undeclared identifier is reported only once for each function it appears in
     *  'LDBL_MAX' undeclared (first use in this function)
     */
    if (number > (unsigned long long)LDBL_MAX) {
        fprintf(stderr, "Input is too large\n");
        return EXIT_FAILURE;
    }

    int digit = first_factorial_digit(number);

    if (digit < 0) {
        fprintf(stderr, "Unable to calculate the first digit\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", digit);
    return EXIT_SUCCESS;
}