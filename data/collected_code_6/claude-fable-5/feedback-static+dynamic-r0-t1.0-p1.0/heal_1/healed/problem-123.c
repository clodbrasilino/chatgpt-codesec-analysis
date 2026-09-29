#include <stdio.h>
#include <stdlib.h>

static long sum_proper_divisors(long n)
{
    long sum;
    long i;

    if (n < 2L) {
        return 0L;
    }

    sum = 1L;
    for (i = 2L; i * i <= n; i++) {
        if (n % i == 0L) {
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

    total = 0L;
    for (a = 2L; a <= limit; a++) {
        long b = sum_proper_divisors(a);
        if (b != a && b > 0L && sum_proper_divisors(b) == a) {
            total += a;
        }
    }
    return total;
}

int main(void)
{
    long limit;
    long result;
    int scanned;

    printf("Enter the upper limit: ");
    scanned = scanf("%ld", &limit);
    if (scanned != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (limit < 1L || limit > 1000000L) {
        fprintf(stderr, "Limit must be between 1 and 1000000\n");
        return EXIT_FAILURE;
    }

    result = sum_amicable_numbers(limit);
    printf("Sum of amicable numbers from 1 to %ld is %ld\n", limit, result);

    return EXIT_SUCCESS;
}