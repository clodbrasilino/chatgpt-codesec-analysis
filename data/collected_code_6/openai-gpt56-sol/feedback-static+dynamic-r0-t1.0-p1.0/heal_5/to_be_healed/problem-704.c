#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'ULONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

static double harmonic_sum(unsigned long n)
{
    double sum = 0.0;
    double compensation = 0.0;

    for (unsigned long i = 1; i <= n; ++i) {
        const double term = 1.0 / (double)i;
        const double adjusted = term - compensation;
        const double next = sum + adjusted;

        compensation = (next - sum) - adjusted;
        sum = next;

        /* Possible weaknesses found:
         *  'ULONG_MAX' undeclared (first use in this function)
         *  use of undeclared identifier 'ULONG_MAX'
         *  each undeclared identifier is reported only once for each function it appears in
         */
        if (i == ULONG_MAX) {
            break;
        }
    }

    return sum;
}

int main(int argc, const char *const argv[])
{
    char *end = NULL;
    unsigned long n;
    double result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    n = strtoul(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' || n == 0) {
        fprintf(stderr, "Invalid positive integer: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    result = harmonic_sum(n);

    if (!isfinite(result)) {
        fputs("Unable to calculate the harmonic sum.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%.17g\n", result);
    return EXIT_SUCCESS;
}