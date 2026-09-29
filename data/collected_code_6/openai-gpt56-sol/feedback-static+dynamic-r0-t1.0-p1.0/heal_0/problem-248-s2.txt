#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static double harmonic_sum_n_minus_one(unsigned long long n)
{
    double sum = 0.0;
    double compensation = 0.0;

    for (unsigned long long i = 1; i < n; ++i) {
        double term = 1.0 / (double)i;
        double adjusted = term - compensation;
        double next = sum + adjusted;

        compensation = (next - sum) - adjusted;
        sum = next;
    }

    return sum;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long long n;
    double result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    n = strtoull(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' || argv[1][0] == '-') {
        fprintf(stderr, "Invalid value for n\n");
        return EXIT_FAILURE;
    }

    result = harmonic_sum_n_minus_one(n);

    if (!isfinite(result)) {
        fprintf(stderr, "Unable to calculate the harmonic sum\n");
        return EXIT_FAILURE;
    }

    printf("%.17g\n", result);
    return EXIT_SUCCESS;
}