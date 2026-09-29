#include <stdio.h>
#include <stdlib.h>

static long long sum_even_factors(long long n)
{
    long long sum = 0;
    long long i;

    if (n <= 0) {
        return 0;
    }

    if (n % 2 != 0) {
        return 0;
    }

    for (i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            if (i % 2 == 0) {
                sum += i;
            }
            if (i != n / i && (n / i) % 2 == 0) {
                sum += n / i;
            }
        }
    }

    return sum;
}

int main(void)
{
    long long n;
    long long result;
    int ret;

    printf("Enter a positive integer: ");
    ret = scanf("%lld", &n);

    if (ret != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (n <= 0) {
        fprintf(stderr, "Error: number must be positive\n");
        return EXIT_FAILURE;
    }

    result = sum_even_factors(n);
    printf("Sum of even factors of %lld is %lld\n", n, result);

    return EXIT_SUCCESS;
}