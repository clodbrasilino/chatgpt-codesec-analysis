#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

long long centered_hexagonal(int n)
{
    if (n < 0) {
        return -1;
    }
    
    long long ln = (long long)n;
    long long term1 = ln - 1;
    
    if (ln > 0 && term1 > LLONG_MAX / ln) {
        return -1;
    }
    
    long long product = ln * term1;
    
    if (product > (LLONG_MAX - 1) / 3) {
        return -1;
    }
    
    return 3LL * product + 1;
}

int main(void)
{
    int n;
    char input[256];
    char *endptr;
    long val;
    long long result;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    val = strtol(input, &endptr, 10);
    if (errno != 0 || endptr == input || (*endptr != '\n' && *endptr != '\0')) {
        return EXIT_FAILURE;
    }

    if (val < 0 || val > INT_MAX) {
        return EXIT_FAILURE;
    }

    n = (int)val;
    result = centered_hexagonal(n);
    if (result == -1) {
        return EXIT_FAILURE;
    }

    printf("%lld\n", result);
    return EXIT_SUCCESS;
}