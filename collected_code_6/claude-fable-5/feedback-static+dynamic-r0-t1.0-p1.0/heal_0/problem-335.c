#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int ap_sum(long long a, long long d, long long n, long long *result)
{
    long long last;
    long long total;

    if (result == NULL || n <= 0) {
        return -1;
    }

    if (d != 0) {
        if ((n - 1) > 0 && (d > 0 ? d : -d) > LLONG_MAX / (n - 1)) {
            return -1;
        }
    }

    last = d * (n - 1);

    if ((last > 0 && a > LLONG_MAX - last) ||
        (last < 0 && a < LLONG_MIN - last)) {
        return -1;
    }

    total = 2 * a + last;

    if (a > LLONG_MAX / 2 || a < LLONG_MIN / 2) {
        return -1;
    }

    if (total != 0 && n > LLONG_MAX / (total > 0 ? total : -total)) {
        return -1;
    }

    total = total * n;

    *result = total / 2;

    return 0;
}

int main(void)
{
    long long a;
    long long d;
    long long n;
    long long sum;

    printf("Enter first term: ");
    if (scanf("%lld", &a) != 1) {
        fprintf(stderr, "Invalid input for first term\n");
        return EXIT_FAILURE;
    }

    printf("Enter common difference: ");
    if (scanf("%lld", &d) != 1) {
        fprintf(stderr, "Invalid input for common difference\n");
        return EXIT_FAILURE;
    }

    printf("Enter number of terms: ");
    if (scanf("%lld", &n) != 1) {
        fprintf(stderr, "Invalid input for number of terms\n");
        return EXIT_FAILURE;
    }

    if (n <= 0) {
        fprintf(stderr, "Number of terms must be positive\n");
        return EXIT_FAILURE;
    }

    if (ap_sum(a, d, n, &sum) != 0) {
        fprintf(stderr, "Computation failed due to invalid input or overflow\n");
        return EXIT_FAILURE;
    }

    printf("Sum of arithmetic progression: %lld\n", sum);

    return EXIT_SUCCESS;
}