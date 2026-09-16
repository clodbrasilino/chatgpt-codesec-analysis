#include <stdio.h>
#include <stdbool.h>

static long sum_of_divisors(long n)
{
    long total;
    long i;

    if (n <= 0) {
        return 0;
    }

    total = 0;
    for (i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            total += i;
            if (i != n / i) {
                total += n / i;
            }
        }
    }

    return total;
}

static bool are_divisor_sums_equal(long a, long b)
{
    return sum_of_divisors(a) == sum_of_divisors(b);
}

int main(void)
{
    long a;
    long b;

    printf("Enter two positive integers: ");
    if (scanf("%ld %ld", &a, &b) != 2) {
        fprintf(stderr, "Error: invalid input.\n");
        return 1;
    }

    if (a <= 0 || b <= 0) {
        fprintf(stderr, "Error: inputs must be positive integers.\n");
        return 1;
    }

    if (are_divisor_sums_equal(a, b)) {
        printf("The sums of divisors of %ld and %ld are the same.\n", a, b);
    } else {
        printf("The sums of divisors of %ld and %ld are not the same.\n", a, b);
    }

    return 0;
}