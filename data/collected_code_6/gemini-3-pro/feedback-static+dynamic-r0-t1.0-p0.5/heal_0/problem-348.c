#include <stdio.h>
#include <stdlib.h>

int count_sequences(int length, int* values, int num_values) {
    if (length <= 0 || values == NULL || num_values <= 0) {
        return 0;
    }

    int max_sum = 0;
    for (int i = 0; i < num_values; i++) {
        if (values[i] > 0) {
            max_sum += values[i];
        }
    }
    max_sum *= length;

    int** dp = (int**)malloc((length + 1) * sizeof(int*));
    if (dp == NULL) {
        return 0;
    }

    for (int i = 0; i <= length; i++) {
        dp[i] = (int*)calloc((max_sum + 1), sizeof(int));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return 0;
        }
    }

    dp[0][0] = 1;

    for (int i = 1; i <= length; i++) {
        for (int j = 0; j <= max_sum; j++) {
            if (dp[i - 1][j] > 0) {
                for (int k = 0; k < num_values; k++) {
                    int next_sum = j + values[k];
                    if (next_sum >= 0 && next_sum <= max_sum) {
                        dp[i][next_sum] += dp[i - 1][j];
                    }
                }
            }
        }
    }

    int total_sequences = 0;
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
    int values[] = {1, -1};
    int num_values = sizeof(values) / sizeof(values[0]);
    int length = 4;

    int result = count_sequences(length, values, num_values);
    printf("%d\n", result);

    return 0;
}