#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int count_divisors(int n)
{
    int count = 0;
    long long v;
    long long i;

    if (n == 0) {
        return -1;
    }

    v = (long long)n;
    if (v < 0) {
        v = -v;
    }

    for (i = 1; i * i <= v; i++) {
        if (v % i == 0) {
            count++;
            if (i != v / i) {
                count++;
            }
        }
    }

    return count;
}

int main(void)
{
    int n;
    int result;

    printf("Enter an integer: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    result = count_divisors(n);
    if (result < 0) {
        fprintf(stderr, "Divisor count is not defined for zero\n");
        return EXIT_FAILURE;
    }

    printf("Number of divisors of %d: %d\n", n, result);
    return EXIT_SUCCESS;
}