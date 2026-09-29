#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int min_perfect_squares(int n) {
    if (n <= 0) {
        return 0;
    }

    int *dp = (int *)malloc((size_t)(n + 1) * sizeof(int));
    if (dp == NULL) {
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i <= n; i++) {
        dp[i] = i;
    }

    for (int i = 2; i <= n; i++) {
        for (int j = 1; j * j <= i; j++) {
            int val = dp[i - j * j] + 1;
            if (val < dp[i]) {
                dp[i] = val;
            }
        }
    }

    int result = dp[n];
    free(dp);
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);

    if (endptr == argv[1] || *endptr != '\0' || errno == ERANGE || val <= 0 || val > INT_MAX) {
        fprintf(stderr, "Number must be a positive 32-bit integer.\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", min_perfect_squares((int)val));
    return EXIT_SUCCESS;
}