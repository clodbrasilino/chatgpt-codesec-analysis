#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int min_squares(int n) {
    if (n < 0) {
        return -1;
    }
    if (n == 0) {
        return 0;
    }

    int *dp = malloc((size_t)(n + 1) * sizeof(int));
    if (dp == NULL) {
        return -1;
    }

    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        dp[i] = INT_MAX;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j * j <= i; j++) {
            int square = j * j;
            if (dp[i - square] != INT_MAX && dp[i - square] + 1 < dp[i]) {
                dp[i] = dp[i - square] + 1;
            }
        }
    }

    int result = dp[n];
    free(dp);
    dp = NULL;
    return result;
}

int main(void) {
    int n;
    printf("Enter a number: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    int result = min_squares(n);
    if (result == -1) {
        fprintf(stderr, "Error: invalid input or memory allocation failure\n");
        return EXIT_FAILURE;
    }

    printf("Minimum number of squares: %d\n", result);
    return EXIT_SUCCESS;
}