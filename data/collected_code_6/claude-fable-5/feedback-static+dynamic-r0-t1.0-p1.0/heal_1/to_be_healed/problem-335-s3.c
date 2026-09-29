#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long ap_sum(long long a, long long d, long long n, int *error)
{
    long long last;
    long long total;

    *error = 0;

    if (n <= 0) {
        *error = 1;
        return 0;
    }

    if (d != 0) {
        if ((n - 1) > 0 && (d > LLONG_MAX / (n - 1) || d < LLONG_MIN / (n - 1))) {
            *error = 1;
            return 0;
        }
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 + 208 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000004,time:1177,execs:720,op:havoc,rep:9)
     */
    last = a + d * (n - 1);

    if ((last > 0 && a > LLONG_MAX - last) || (last < 0 && a < LLONG_MIN - last)) {
        *error = 1;
        return 0;
    }

    total = a + last;

    if (total % 2 == 0) {
        total = total / 2;
        if (total != 0 && (n > LLONG_MAX / (total > 0 ? total : -total))) {
            *error = 1;
            return 0;
        }
        return total * n;
    } else {
        if (n % 2 != 0) {
            *error = 1;
            return 0;
        }
        long long half_n = n / 2;
        if (total != 0 && (half_n > LLONG_MAX / (total > 0 ? total : -total))) {
            *error = 1;
            return 0;
        }
        return total * half_n;
    }
}

int main(void)
{
    long long a;
    long long d;
    long long n;
    long long result;
    int error;

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

    result = ap_sum(a, d, n, &error);

    if (error != 0) {
        fprintf(stderr, "Computation error: invalid input or overflow\n");
        return EXIT_FAILURE;
    }

    printf("Sum of arithmetic progression: %lld\n", result);

    return EXIT_SUCCESS;
}