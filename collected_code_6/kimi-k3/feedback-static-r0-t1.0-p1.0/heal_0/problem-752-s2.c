#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

unsigned long long jacobsthal(int n)
{
    if (n < 0) {
        return 0;
    }
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }

    unsigned long long prev2 = 0;
    unsigned long long prev1 = 1;
    unsigned long long current = 0;

    for (int i = 2; i <= n; i++) {
        if (prev1 > (ULLONG_MAX - prev2) / 2) {
            return 0;
        }
        current = 2 * prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }

    return current;
}

int main(void)
{
    int n;
    char buffer[256];
    char *endptr;
    long val;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    val = strtol(buffer, &endptr, 10);
    if (errno != 0 || endptr == buffer || val < 0 || val > INT_MAX) {
        return EXIT_FAILURE;
    }

    n = (int)val;

    if (n > 63) {
        return EXIT_FAILURE;
    }

    printf("%llu\n", jacobsthal(n));

    return EXIT_SUCCESS;
}