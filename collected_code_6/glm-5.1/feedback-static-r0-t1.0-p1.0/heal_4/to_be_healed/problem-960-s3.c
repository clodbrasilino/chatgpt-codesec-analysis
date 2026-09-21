#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

int tiling(int n) {
    if (n < 1) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    if (n == 2) {
        return 2;
    }

    if (n > 46) {
        return -1;
    }

    int dp[3];
    dp[0] = 1;
    dp[1] = 2;

    for (int i = 2; i < n; i++) {
        dp[2] = dp[1] + dp[0];
        dp[0] = dp[1];
        dp[1] = dp[2];
    }

    return dp[1];
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <length>\n", argv[0]);
        return 1;
    }

    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);
    if (errno == ERANGE || val > 46 || val <= 0 || *endptr != '\0') {
        fprintf(stderr, "Length must be a positive integer within valid range.\n");
        return 1;
    }
    int n = (int)val;

    int result = tiling(n);
    if (result == -1) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    printf("%d\n", result);

    return 0;
}