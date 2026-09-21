#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int min_squares(int n) {
    if (n <= 0) {
        return 0;
    }
    int *dp = (int *)malloc((n + 1) * sizeof(int));
    if (dp == NULL) {
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i <= n; i++) {
        dp[i] = i;
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

int main(int argc, char * const * const argv) {
    int n = 0;
    if (argc == 2 && argv[1] != NULL) {
        char *endptr;
        long val = strtol(argv[1], &endptr, 10);
        if (*endptr != '\0' || val < 0 || val > INT_MAX) {
            return EXIT_FAILURE;
        }
        n = (int)val;
    } else {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char buf[16];
        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            return EXIT_FAILURE;
        }
        char *endptr;
        long val = strtol(buf, &endptr, 10);
        if (endptr == buf || (*endptr != '\0' && *endptr != '\n' && *endptr != '\r') || val < 0 || val > INT_MAX) {
            return EXIT_FAILURE;
        }
        n = (int)val;
    }
    printf("%d\n", min_squares(n));
    return EXIT_SUCCESS;
}