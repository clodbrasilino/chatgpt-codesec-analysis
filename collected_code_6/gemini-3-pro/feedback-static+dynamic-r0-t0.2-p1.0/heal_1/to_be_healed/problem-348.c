#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Possible weaknesses found:
 *  Parameter 'values' can be declared as pointer to const [constParameterPointer]
 */
long long count_sequences(int length, int* values, int num_values) {
    if (length <= 0 || values == NULL || num_values <= 0) {
        return 0;
    }

    int max_val = 0;
    for (int i = 0; i < num_values; i++) {
        if (values[i] > max_val) {
            max_val = values[i];
        }
    }

    int max_sum = max_val * length;
    long long* dp = (long long*)calloc(max_sum + 1, sizeof(long long));
    long long* next_dp = (long long*)calloc(max_sum + 1, sizeof(long long));

    if (dp == NULL || next_dp == NULL) {
        free(dp);
        free(next_dp);
        return 0;
    }

    dp[0] = 1;

    for (int i = 0; i < length; i++) {
        memset(next_dp, 0, (max_sum + 1) * sizeof(long long));
        for (int j = 0; j <= max_sum; j++) {
            if (dp[j] > 0) {
                for (int k = 0; k < num_values; k++) {
                    int next_sum = j + values[k];
                    if (next_sum >= 0 && next_sum <= max_sum) {
                        next_dp[next_sum] += dp[j];
                    }
                }
            }
        }
        long long* temp = dp;
        dp = next_dp;
        next_dp = temp;
    }

    long long total_sequences = 0;
    for (int j = 0; j <= max_sum; j++) {
        total_sequences += dp[j];
    }

    free(dp);
    free(next_dp);

    return total_sequences;
}

int main() {
    int length = 3;
    int values[] = {-1, 1};
    int num_values = sizeof(values) / sizeof(values[0]);

    long long result = count_sequences(length, values, num_values);
    printf("%lld\n", result);

    return 0;
}