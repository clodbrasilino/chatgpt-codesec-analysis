#include <stdio.h>
#include <stdlib.h>

int count_sequences(int *values, int values_count, int length) {
    if (values == NULL || values_count <= 0 || length <= 0) {
        return 0;
    }

    int *dp = (int *)calloc((size_t)length + 1, sizeof(int));
    if (dp == NULL) {
        return -1;
    }

    int *prefix = (int *)calloc((size_t)length + 1, sizeof(int));
    if (prefix == NULL) {
        free(dp);
        return -1;
    }

    dp[0] = 1;
    prefix[0] = 1;

    for (int pos = 1; pos <= length; pos++) {
        dp[pos] = 0;
        for (int i = 0; i < values_count; i++) {
            int prev_sum = pos - values[i];
            if (prev_sum >= 0) {
                dp[pos] += dp[prev_sum];
            }
        }
        prefix[pos] = prefix[pos - 1] + dp[pos];
    }

    int result = 0;
    for (int pos = 0; pos <= length; pos++) {
        result += dp[pos];
    }

    free(dp);
    free(prefix);

    return result;
}

int main(void) {
    int values[] = {1, 2};
    int length = 4;
    int result = count_sequences(values, 2, length);
    printf("%d\n", result);
    return 0;
}