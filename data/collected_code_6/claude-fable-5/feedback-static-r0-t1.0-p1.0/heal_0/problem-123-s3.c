#include <stdio.h>
#include <stdlib.h>

static long sum_of_proper_divisors(long n)
{
    long sum;
    long i;

    if (n <= 1) {
        return 0;
    }

    sum = 1;
    for (i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) {
                sum += n / i;
            }
        }
    }
    return sum;
}

static long sum_amicable_numbers(long limit)
{
    long total;
    long a;
    long b;

    total = 0;
    for (a = 2; a <= limit; a++) {
        b = sum_of_proper_divisors(a);
        if (b != a && b > 0 && sum_of_proper_divisors(b) == a) {
            total += a;
        }
    }
    return total;
}

int main(void)
{
    long limit;
    long result;
    int scan_result;

    printf("Enter the upper limit: ");
    scan_result = scanf("%ld", &limit);

    if (scan_result != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (limit < 1) {
        fprintf(stderr, "Error: limit must be at least 1\n");
        return EXIT_FAILURE;
    }

    if (limit > 1000000L) {
        fprintf(stderr, "Error: limit too large\n");
        return EXIT_FAILURE;
    }

    result = sum_amicable_numbers(limit);
    printf("Sum of amicable numbers from 1 to %ld: %ld\n", limit, result);

    return EXIT_SUCCESS;
}