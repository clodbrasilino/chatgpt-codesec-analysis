#include <stdio.h>
#include <stdlib.h>

static unsigned long long sum_of_divisors(unsigned long long n)
{
    unsigned long long sum = 0;
    unsigned long long i;

    if (n == 0) {
        return 0;
    }

    for (i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) {
                sum += n / i;
            }
        }
    }

    return sum;
}

int main(void)
{
    unsigned long long n;
    int result;

    printf("Enter a positive integer: ");
    result = scanf("%llu", &n);

    if (result != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (n == 0) {
        fprintf(stderr, "Error: number must be greater than zero\n");
        return EXIT_FAILURE;
    }

    printf("Sum of divisors of %llu is %llu\n", n, sum_of_divisors(n));

    return EXIT_SUCCESS;
}