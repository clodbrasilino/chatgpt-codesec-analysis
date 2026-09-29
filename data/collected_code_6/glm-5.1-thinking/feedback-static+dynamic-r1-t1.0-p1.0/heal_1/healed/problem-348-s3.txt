#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long count_sequences(const int *values, int num_values, int length) {
    if (length == 0) return 1;
    if (num_values <= 0 || values == NULL) return 0;

    int max_val = INT_MIN;
    for (int i = 0; i < num_values; i++) {
        if (values[i] > max_val) max_val = values[i];
    }

    long long max_sum_ll = (long long)length * max_val;
    if (max_sum_ll < 0) return 0;
    if (max_sum_ll > 1000000) return -1;
    int max_sum = (int)max_sum_ll;

    long long **dp = (long long **)malloc((length + 1) * sizeof(long long *));
    if (dp == NULL) return -1;
    for (int i = 0; i <= length; i++) {
        dp[i] = (long long *)calloc(max_sum + 1, sizeof(long long));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) free(dp[j]);
            free(dp);
            return -1;
        }
    }

    dp[0][0] = 1;

    for (int i = 0; i < length; i++) {
        for (int j = 0; j <= max_sum; j++) {
            if (dp[i][j] > 0) {
                for (int k = 0; k < num_values; k++) {
                    int new_sum = j + values[k];
                    if (new_sum >= 0 && new_sum <= max_sum) {
                        dp[i + 1][new_sum] += dp[i][j];
                    }
                }
            }
        }
    }

    long long total = 0;
    for (int j = 0; j <= max_sum; j++) {
        total += dp[length][j];
    }

    for (int i = 0; i <= length; i++) free(dp[i]);
    free(dp);

    return total;
}

int main(void) {
    int values[] = {1, -1};
    int num_values = sizeof(values) / sizeof(values[0]);
    int length = 4;

    long long result = count_sequences(values, num_values, length);
    if (result >= 0) {
        printf("%lld\n", result);
    } else {
        fprintf(stderr, "Error: memory allocation failed or input too large\n");
        return 1;
    }

    return 0;
}