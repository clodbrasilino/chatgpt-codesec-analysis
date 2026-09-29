#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

unsigned long long count_valid_sequences(size_t length, const int *values, size_t num_values);

unsigned long long count_valid_sequences(size_t length, const int *values, size_t num_values) {
    if (values == NULL || num_values == 0) {
        return 0;
    }
    if (length == 0) {
        return 1;
    }

    int max_val = 0;
    for (size_t i = 0; i < num_values; ++i) {
        if (values[i] > max_val) {
            max_val = values[i];
        }
    }

    if (max_val > 0 && length > SIZE_MAX / (size_t)max_val) {
        return 0;
    }

    size_t max_sum = length * (size_t)max_val;
    if (max_sum > (SIZE_MAX / sizeof(unsigned long long)) - 1) {
        return 0;
    }

    unsigned long long *prev_dp = (unsigned long long *)calloc(max_sum + 1, sizeof(unsigned long long));
    unsigned long long *curr_dp = (unsigned long long *)calloc(max_sum + 1, sizeof(unsigned long long));

    if (prev_dp == NULL || curr_dp == NULL) {
        free(prev_dp);
        free(curr_dp);
        return 0;
    }

    prev_dp[0] = 1;

    for (size_t i = 1; i <= length; ++i) {
        for (size_t j = 0; j <= max_sum; ++j) {
            curr_dp[j] = 0;
        }
        
        size_t prev_max_sum = (i - 1) * (size_t)max_val;
        for (size_t j = 0; j <= prev_max_sum; ++j) {
            if (prev_dp[j] > 0) {
                for (size_t k = 0; k < num_values; ++k) {
                    long long next_sum = (long long)j + values[k];
                    if (next_sum >= 0 && (size_t)next_sum <= max_sum) {
                        curr_dp[(size_t)next_sum] += prev_dp[j];
                    }
                }
            }
        }
        
        unsigned long long *temp = prev_dp;
        prev_dp = curr_dp;
        curr_dp = temp;
    }

    unsigned long long total_sequences = 0;
    for (size_t j = 0; j <= max_sum; ++j) {
        total_sequences += prev_dp[j];
    }

    free(prev_dp);
    free(curr_dp);

    return total_sequences;
}

int main(void) {
    int values[] = {1, -1};
    size_t num_values = sizeof(values) / sizeof(values[0]);
    size_t length = 4;
    
    unsigned long long result = count_valid_sequences(length, values, num_values);
    printf("%llu\n", result);
    
    return 0;
}