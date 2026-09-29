#include <stdio.h>
#include <stdlib.h>

unsigned long long count_sequences(int length, const int *values, size_t num_values) {
    if (length < 0 || values == NULL || num_values == 0) {
        return 0;
    }
    if (length == 0) {
        return 1;
    }

    int max_val = 0;
    for (size_t i = 0; i < num_values; i++) {
        if (values[i] > max_val) {
            max_val = values[i];
        }
    }

    long long max_sum_ll = (long long)length * (long long)max_val;
    if (max_sum_ll < 0) {
        max_sum_ll = 0;
    }

    size_t dp_size = (size_t)(max_sum_ll + 1);
    unsigned long long *dp = (unsigned long long *)calloc(dp_size, sizeof(unsigned long long));
    if (dp == NULL) {
        return 0;
    }

    unsigned long long *next_dp = (unsigned long long *)calloc(dp_size, sizeof(unsigned long long));
    if (next_dp == NULL) {
        free(dp);
        return 0;
    }

    dp[0] = 1;

    for (int i = 0; i < length; i++) {
        for (size_t j = 0; j < dp_size; j++) {
            next_dp[j] = 0;
        }

        for (size_t s = 0; s < dp_size; s++) {
            if (dp[s] > 0) {
                for (size_t k = 0; k < num_values; k++) {
                    long long next_sum = (long long)s + (long long)values[k];
                    if (next_sum >= 0 && next_sum < (long long)dp_size) {
                        next_dp[(size_t)next_sum] += dp[s];
                    }
                }
            }
        }

        for (size_t j = 0; j < dp_size; j++) {
            dp[j] = next_dp[j];
        }
    }

    unsigned long long total_sequences = 0;
    for (size_t s = 0; s < dp_size; s++) {
        total_sequences += dp[s];
    }

    free(dp);
    free(next_dp);

    return total_sequences;
}

int main(void) {
    int values[] = {1, -1, 2};
    size_t num_values = sizeof(values) / sizeof(values[0]);
    int length = 5;

    unsigned long long result = count_sequences(length, values, num_values);
    printf("%llu\n", result);

    return 0;
}