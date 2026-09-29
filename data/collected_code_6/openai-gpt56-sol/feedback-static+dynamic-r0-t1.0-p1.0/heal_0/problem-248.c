#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static double harmonic_sum(unsigned long n)
{
    double sum = 0.0;

    for (unsigned long i = 1; i < n; ++i) {
        sum += 1.0 / (double)i;
    }

    return sum;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    unsigned long n = strtoul(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' || n == 0) {
        fprintf(stderr, "Invalid positive integer: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    printf("%.17g\n", harmonic_sum(n));
    return EXIT_SUCCESS;
}