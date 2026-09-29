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

int main(int argc, char * const argv[]) {
    int n;
    if (argc != 2) {
        if (scanf("%d", &n) != 1 || n < 0) {
            return EXIT_FAILURE;
        }
    } else {
        char *endptr;
        long val = strtol(argv[1], &endptr, 10);
        if (*endptr != '\0' || val < 0 || val > INT_MAX) {
            return EXIT_FAILURE;
        }
        n = (int)val;
    }
    printf("%d\n", min_squares(n));
    return EXIT_SUCCESS;
}