#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

unsigned long long add_saturate(unsigned long long a, unsigned long long b) {
    if (ULLONG_MAX - a < b) {
        return ULLONG_MAX;
    }
    return a + b;
}

unsigned long long count_sequences(int length, const int *values, size_t num_values) {
    if (length < 0 || values == NULL || num_values == 0) {
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

    if (max_val > 0) {
        if ((size_t)max_val > (SIZE_MAX - 1) / (size_t)length) {
            return 0;
        }
    }

    size_t max_sum = (size_t)length * max_val;
    size_t array_size = max_sum + 1;

    unsigned long long *prev_dp = (unsigned long long *)calloc(array_size, sizeof(unsigned long long));
    if (prev_dp == NULL) {
        return 0;
    }

    unsigned long long *next_dp = (unsigned long long *)calloc(array_size, sizeof(unsigned long long));
    if (next_dp == NULL) {
        free(prev_dp);
        return 0;
    }

    prev_dp[0] = 1;

    for (int step = 1; step <= length; ++step) {
        memset(next_dp, 0, array_size * sizeof(unsigned long long));
        size_t prev_max_sum = (size_t)(step - 1) * max_val;

        for (size_t current_sum = 0; current_sum <= prev_max_sum; ++current_sum) {
            if (prev_dp[current_sum] > 0) {
                for (size_t i = 0; i < num_values; ++i) {
                    int v = values[i];
                    if (v >= 0) {
                        size_t next_sum = current_sum + (size_t)v;
                        if (next_sum < array_size) {
                            next_dp[next_sum] = add_saturate(next_dp[next_sum], prev_dp[current_sum]);
                        }
                    } else {
                        size_t abs_v = (size_t)(-(long long)v);
                        if (current_sum >= abs_v) {
                            size_t next_sum = current_sum - abs_v;
                            if (next_sum < array_size) {
                                next_dp[next_sum] = add_saturate(next_dp[next_sum], prev_dp[current_sum]);
                            }
                        }
                    }
                }
            }
        }

        for (size_t i = 0; i <= (size_t)step * max_val; ++i) {
            prev_dp[i] = next_dp[i];
        }
    }

    unsigned long long total_sequences = 0;
    size_t final_max_sum = (size_t)length * max_val;
    
    for (size_t i = 0; i <= final_max_sum; ++i) {
        total_sequences = add_saturate(total_sequences, prev_dp[i]);
    }

    free(prev_dp);
    free(next_dp);

    return total_sequences;
}

int main(void) {
    int values[] = {1, -1, 2, -2};
    size_t num_values = sizeof(values) / sizeof(values[0]);
    int length = 5;

    unsigned long long result = count_sequences(length, values, num_values);
    printf("%llu\n", result);

    return 0;
}