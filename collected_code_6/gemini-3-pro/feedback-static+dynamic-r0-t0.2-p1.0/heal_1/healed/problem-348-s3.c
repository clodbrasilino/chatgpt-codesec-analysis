#include <stdio.h>
#include <stdlib.h>

long long count_sequences(int length, const int* values, int num_values) {
    if (length < 0 || values == NULL || num_values <= 0) {
        return 0;
    }

    int max_sum = 0;
    for (int i = 0; i < num_values; i++) {
        if (values[i] > 0) {
            max_sum += values[i];
        }
    }
    max_sum *= length;

    long long** dp = (long long**)malloc((length + 1) * sizeof(long long*));
    if (dp == NULL) {
        return 0;
    }

    for (int i = 0; i <= length; i++) {
        dp[i] = (long long*)calloc((max_sum + 1), sizeof(long long));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return 0;
        }
    }

    dp[0][0] = 1;

    for (int i = 0; i < length; i++) {
        for (int j = 0; j <= max_sum; j++) {
            if (dp[i][j] > 0) {
                for (int k = 0; k < num_values; k++) {
                    int next_sum = j + values[k];
                    if (next_sum >= 0 && next_sum <= max_sum) {
                        dp[i + 1][next_sum] += dp[i][j];
                    }
                }
            }
        }
    }

    long long total_sequences = 0;
    for (int j = 0; j <= max_sum; j++) {
        total_sequences += dp[length][j];
    }

    for (int i = 0; i <= length; i++) {
        free(dp[i]);
    }
    free(dp);

    return total_sequences;
}

int main() {
    int length = 3;
    int values[] = {1, -1};
    int num_values = sizeof(values) / sizeof(values[0]);

    long long result = count_sequences(length, values, num_values);
    printf("%lld\n", result);

    return 0;
}