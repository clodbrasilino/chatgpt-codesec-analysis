#include <stdio.h>
#include <stdlib.h>

int min_perfect_squares(int n) {
    if (n <= 0) {
        return 0;
    }

    int *dp = (int *)malloc((n + 1) * sizeof(int));
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

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    long val = strtol(argv[1], NULL, 10);
    if (val <= 0 || val > 2147483647) {
        fprintf(stderr, "Number must be a positive 32-bit integer.\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", min_perfect_squares((int)val));
    return EXIT_SUCCESS;
}