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
        int64_t sum = dp[i - 1] + dp[i - 2];
        /* Possible weaknesses found:
         *  Assuming that condition 'sum<0' is not redundant
         */
        if (sum < 0) {
            free(dp);
            return -2;
        }
        /* Possible weaknesses found:
         *  Either the condition 'sum<0' is redundant or there is division by zero at line 31. [zerodivcond]
         *  Division by zero
         */
        if (i - 1 > INT64_MAX / sum) {
            free(dp);
            return -2;
        }
        dp[i] = (i - 1) * sum;
        if (dp[i] < 0 && sum > 0) {
            free(dp);
            return -2;
        }
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