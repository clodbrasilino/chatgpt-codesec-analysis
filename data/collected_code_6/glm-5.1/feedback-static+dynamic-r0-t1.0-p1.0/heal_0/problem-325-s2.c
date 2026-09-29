#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, char *argv[]) {
    int n;
    if (argc != 2) {
        if (scanf("%d", &n) != 1 || n < 0) {
            return EXIT_FAILURE;
        }
    } else {
        n = atoi(argv[1]);
        if (n < 0) {
            return EXIT_FAILURE;
        }
    }
    printf("%d\n", min_squares(n));
    return EXIT_SUCCESS;
}