#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long count_sequences(int length, int* values, int num_values) {
    if (length < 0 || num_values <= 0 || values == NULL) {
        return 0;
    }

    if (length == 0) {
        return 1;
    }

    int max_val = 0;
    for (int i = 0; i < num_values; i++) {
        if (values[i] > max_val) {
            max_val = values[i];
        }
    }

    int max_sum = length * max_val;
    long long* dp = (long long*)calloc(max_sum + 1, sizeof(long long));
    long long* next_dp = (long long*)calloc(max_sum + 1, sizeof(long long));

    if (dp == NULL || next_dp == NULL) {
        free(dp);
        free(next_dp);
        return 0;
    }

    dp[0] = 1;

    for (int step = 0; step < length; step++) {
        memset(next_dp, 0, (max_sum + 1) * sizeof(long long));
        for (int sum = 0; sum <= max_sum; sum++) {
            if (dp[sum] > 0) {
                for (int i = 0; i < num_values; i++) {
                    int next_sum = sum + values[i];
                    if (next_sum >= 0 && next_sum <= max_sum) {
                        next_dp[next_sum] += dp[sum];
                    }
                }
            }
        }
        long long* temp = dp;
        dp = next_dp;
        next_dp = temp;
    }

    long long total_sequences = 0;
    for (int sum = 0; sum <= max_sum; sum++) {
        total_sequences += dp[sum];
    }

    free(dp);
    free(next_dp);

    return total_sequences;
}

int main(void) {
    int values[] = {1, -1};
    int num_values = sizeof(values) / sizeof(values[0]);
    int length = 4;

    long long result = count_sequences(length, values, num_values);
    printf("%lld\n", result);

    return 0;
}