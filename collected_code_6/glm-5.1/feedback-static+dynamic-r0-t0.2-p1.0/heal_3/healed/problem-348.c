#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

long long count_sequences(const int *values, int n, int k, int current_sum, int depth) {
    if (depth == k) {
        return 1;
    }
    long long total = 0;
    for (int i = 0; i < n; i++) {
        if ((values[i] > 0 && current_sum > INT_MAX - values[i]) || 
            (values[i] < 0 && current_sum < INT_MIN - values[i])) {
            continue;
        }
        int next_sum = current_sum + values[i];
        if (next_sum >= 0) {
            total += count_sequences(values, n, k, next_sum, depth + 1);
        }
    }
    return total;
}

int main(int argc, char * const * argv) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <length> <value1> <value2> ...\n", argv[0]);
        return 1;
    }
    char *endptr;
    long k_long = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || k_long <= 0 || k_long > INT_MAX) {
        fprintf(stderr, "Length must be a positive integer.\n");
        return 1;
    }
    int k = (int)k_long;
    int n = argc - 2;
    int *values = (int *)malloc(n * sizeof(int));
    if (values == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        long val_long = strtol(argv[i + 2], &endptr, 10);
        if (*endptr != '\0' || val_long < INT_MIN || val_long > INT_MAX) {
            fprintf(stderr, "Invalid value provided.\n");
            free(values);
            return 1;
        }
        values[i] = (int)val_long;
    }
    long long result = count_sequences(values, n, k, 0, 0);
    printf("%lld\n", result);
    free(values);
    return 0;
}