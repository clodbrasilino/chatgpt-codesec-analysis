#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

static int calculate_sum_and_average(unsigned long long n,
                                     unsigned long long *sum,
                                     long double *average)
{
    unsigned long long left;
    unsigned long long right;

    if (sum == NULL || average == NULL || n == 0 || n == ULLONG_MAX) {
        return -1;
    }

    if ((n & 1ULL) == 0) {
        left = n / 2;
        right = n + 1;
    } else {
        left = n;
        right = (n / 2) + 1;
    }

    if (left > ULLONG_MAX / right) {
        return -1;
    }

    *sum = left * right;
    *average = ((long double)n + 1.0L) / 2.0L;

    return 0;
}

int main(void)
{
    char input[128];
    char *end;
    unsigned long long n;
    unsigned long long sum;
    long double average;
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    n = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input || n == 0) {
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    if (calculate_sum_and_average(n, &sum, &average) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("Sum: %llu\nAverage: %.2Lf\n", sum, average) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}