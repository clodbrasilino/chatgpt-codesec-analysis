#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

int64_t rencontres_number(int n) {
    if (n < 0) {
        return -1;
    }
    if (n == 0) {
        return 1;
    }
    if (n == 1) {
        return 0;
    }

    int64_t *dp = (int64_t *)malloc((n + 1) * sizeof(int64_t));
    if (dp == NULL) {
        return -1;
    }

    dp[0] = 1;
    dp[1] = 0;

    for (int i = 2; i <= n; i++) {
        int64_t term1 = dp[i - 1];
        int64_t term2 = dp[i - 2];
        
        if (term1 > INT64_MAX - term2) {
            free(dp);
            return -2;
        }
        
        int64_t sum = term1 + term2;
        
        if (sum > INT64_MAX / (i - 1)) {
            free(dp);
            return -2;
        }
        
        dp[i] = (i - 1) * sum;
    }

    int64_t result = dp[n];
    free(dp);
    return result;
}

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    int64_t result = rencontres_number(n);
    if (result == -1) {
        fprintf(stderr, "Error computing rencontres number\n");
        return 1;
    }
    if (result == -2) {
        fprintf(stderr, "Overflow detected\n");
        return 1;
    }

    printf("D_%d = %" PRId64 "\n", n, result);
    return 0;
}