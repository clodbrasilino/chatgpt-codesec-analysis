#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long jacobsthal_lucas(int n)
{
    if (n == 0) {
        return 2;
    }
    if (n == 1) {
        return 1;
    }

    long long prev2 = 2;
    long long prev1 = 1;
    long long current = 0;
    int i;

    for (i = 2; i <= n; i++) {
        if (prev1 > LLONG_MAX - 2 * prev2) {
            return -1;
        }
        current = prev1 + 2 * prev2;
        prev2 = prev1;
        prev1 = current;
    }

    return current;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *endptr;
    long val;
    int n;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    val = strtol(buffer, &endptr, 10);

    if (errno != 0 || endptr == buffer || val < 0 || val > INT_MAX) {
        return EXIT_FAILURE;
    }

    n = (int)val;
    printf("%lld\n", jacobsthal_lucas(n));

    return EXIT_SUCCESS;
}