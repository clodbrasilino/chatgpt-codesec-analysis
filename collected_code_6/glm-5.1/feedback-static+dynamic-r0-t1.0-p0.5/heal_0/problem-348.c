#include <stdio.h>
#include <stdlib.h>

int count_sequences(int *values, int n, int k, int index, int current_sum, int *buffer, int buffer_index) {
    if (current_sum < 0) {
        return 0;
    }
    if (index == k) {
        return 1;
    }
    int total = 0;
    for (int i = 0; i < n; i++) {
        buffer[buffer_index] = values[i];
        total += count_sequences(values, n, k, index + 1, current_sum + values[i], buffer, buffer_index + 1);
    }
    return total;
}

int count_non_negative_prefix_sums(int *values, int n, int k) {
    if (values == NULL || n <= 0 || k < 0) {
        return 0;
    }
    if (k == 0) {
        return 1;
    }
    int *buffer = (int *)malloc(k * sizeof(int));
    if (buffer == NULL) {
        return 0;
    }
    int result = count_sequences(values, n, k, 0, 0, buffer, 0);
    free(buffer);
    return result;
}

int main() {
    int values[] = {1, -1, 2};
    int n = sizeof(values) / sizeof(values[0]);
    int k = 3;
    int result = count_non_negative_prefix_sums(values, n, k);
    printf("%d\n", result);
    return 0;
}