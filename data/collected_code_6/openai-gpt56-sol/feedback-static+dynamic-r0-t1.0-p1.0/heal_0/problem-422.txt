#include <stdio.h>
#include <stdlib.h>

static int average_of_cubes(unsigned long long n, long double *average)
{
    long double count;
    long double sum;

    if (n == 0 || average == NULL) {
        return -1;
    }

    count = (long double)n;
    sum = count * (count + 1.0L) / 2.0L;
    *average = (sum * sum) / count;

    return 0;
}

int main(void)
{
    unsigned long long n;
    long double average;

    if (printf("Enter n: ") < 0) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (scanf("%llu", &n) != 1 || n == 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (average_of_cubes(n, &average) != 0) {
        fprintf(stderr, "Unable to calculate average\n");
        return EXIT_FAILURE;
    }

    if (printf("Average: %.10Lf\n", average) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}