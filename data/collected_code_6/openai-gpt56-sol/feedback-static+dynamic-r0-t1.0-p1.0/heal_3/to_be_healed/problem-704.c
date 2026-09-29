#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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
    }

    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
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