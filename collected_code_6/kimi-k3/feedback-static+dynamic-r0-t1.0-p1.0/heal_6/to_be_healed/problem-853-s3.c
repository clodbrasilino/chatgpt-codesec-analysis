#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

long long sum_odd_factors(long long n)
{
    long long sum = 0;
    long long i;

    if (n < 0) {
        if (n == LLONG_MIN) {
            return -1;
        }
        n = -n;
    }

    while ((n & 1) == 0 && n != 0) {
        n >>= 1;
    }

    for (i = 1; i <= n / i; i += 2) {
        if (n % i == 0) {
            long long pair = n / i;
            sum += i;
            if (pair != i) {
                sum += pair;
            }
        }
    }

    return sum;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *endptr;
    long long num;
    char *p;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    p = input;
    while (isspace((unsigned char)*p)) {
        p++;
    }

    errno = 0;
    num = strtoll(p, &endptr, 10);

    if (errno == ERANGE || endptr == p) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*endptr)) {
        endptr++;
    }

    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("%lld\n", sum_odd_factors(num));

    return EXIT_SUCCESS;
}