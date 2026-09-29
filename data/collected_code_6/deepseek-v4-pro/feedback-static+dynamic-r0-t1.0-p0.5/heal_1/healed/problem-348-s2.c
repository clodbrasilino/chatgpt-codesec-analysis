#include <stdio.h>
#include <stdlib.h>

static long long count_sequences_recursive(int *values, int values_count, int length, int current_sum, long long **memo, int offset) {
    if (length == 0) {
        return current_sum >= 0 ? 1 : 0;
    }
    
    if (current_sum < 0) {
        return 0;
    }
    
    if (memo[length][current_sum + offset] != -1) {
        return memo[length][current_sum + offset];
    }
    
    long long total = 0;
    for (int i = 0; i < values_count; i++) {
        total += count_sequences_recursive(values, values_count, length - 1, current_sum + values[i], memo, offset);
    }
    
    memo[length][current_sum + offset] = total;
    return total;
}

long long count_sequences(int *values, int values_count, int length) {
    if (values == NULL || values_count <= 0 || length < 0) {
        return 0;
    }
    
    int max_sum = 0;
    for (int i = 0; i < values_count; i++) {
        if (values[i] > 0) {
            max_sum += values[i];
        }
    }
    max_sum *= length;
    
    int min_sum = 0;
    for (int i = 0; i < values_count; i++) {
        if (values[i] < 0) {
            min_sum += values[i];
        }
    }
    min_sum *= length;
    
    int offset = -min_sum;
    int memo_size = max_sum - min_sum + 1;
    
    long long **memo = (long long **)malloc((length + 1) * sizeof(long long *));
    if (memo == NULL) {
        return 0;
    }
    
    for (int i = 0; i <= length; i++) {
        memo[i] = (long long *)malloc(memo_size * sizeof(long long));
        if (memo[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(memo[j]);
            }
            free(memo);
            return 0;
        }
        for (int j = 0; j < memo_size; j++) {
            memo[i][j] = -1;
        }
    }
    
    long long result = count_sequences_recursive(values, values_count, length, 0, memo, offset);
    
    for (int i = 0; i <= length; i++) {
        free(memo[i]);
    }
    free(memo);
    
    return result;
}

int main(void) {
    int values[] = {-1, 1};
    int values_count = sizeof(values) / sizeof(values[0]);
    int length = 3;
    
    long long result = count_sequences(values, values_count, length);
    printf("%lld\n", result);
    
    return 0;
}