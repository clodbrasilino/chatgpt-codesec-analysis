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
    int result;

    printf("Enter n: ");
    if (scanf("%llu", &n) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    result = average_of_cubes(n, &average);
    if (result != 0) {
        fprintf(stderr, "n must be greater than zero.\n");
        return EXIT_FAILURE;
    }

    printf("Average of cubes: %.10Lf\n", average);
    return EXIT_SUCCESS;
}