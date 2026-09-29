#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

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
        current = prev1 + 2 * prev2;
        prev2 = prev1;
        prev1 = current;
    }

    return current;
}

int main(void)
{
    int n;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    char *endptr;
    long val;
    size_t len;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    len = strnlen(buffer, sizeof(buffer));
    if (len == sizeof(buffer)) {
        return EXIT_FAILURE;
    }
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    errno = 0;
    val = strtol(buffer, &endptr, 10);

    if (errno != 0 || endptr == buffer || val < 0 || val > INT_MAX) {
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*endptr)) {
        endptr++;
    }

    if (*endptr != '\0') {
        return EXIT_FAILURE;
    }

    n = (int)val;

    if (n > 63) {
        return EXIT_FAILURE;
    }

    printf("%llu\n", jacobsthal(n));

    return EXIT_SUCCESS;
}