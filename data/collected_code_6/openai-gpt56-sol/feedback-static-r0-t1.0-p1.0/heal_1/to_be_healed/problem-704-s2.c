#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int harmonic_sum(unsigned long n, long double *result)
{
    if (result == NULL || n == 0UL) {
        return -1;
    }

    long double sum = 0.0L;
    long double compensation = 0.0L;

    for (unsigned long i = 1UL; i < n; ++i) {
        long double term = 1.0L / (long double)i;
        long double adjusted = term - compensation;
        long double updated = sum + adjusted;
        compensation = (updated - sum) - adjusted;
        sum = updated;
    }

    *result = sum;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    if (argc != 2) {
        (void)fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    unsigned long n = strtoul(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' || n == 0UL) {
        (void)fprintf(stderr, "Invalid positive integer: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    long double result = 0.0L;

    if (harmonic_sum(n, &result) != 0 || !isfinite(result)) {
        (void)fprintf(stderr, "Unable to calculate the harmonic sum.\n");
        return EXIT_FAILURE;
    }

    if (printf("%.18Lg\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}