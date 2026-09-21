#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

long long count_sequences(int *values, int n, int k, long long current_sum, int depth) {
    if (current_sum < 0) {
        return 0;
    }
    if (depth == k) {
        return 1;
    }
    long long total = 0;
    for (int i = 0; i < n; i++) {
        total += count_sequences(values, n, k, current_sum + values[i], depth + 1);
    }
    return total;
}

int main(int argc, char * const argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <length> <value1> <value2> ...\n", argv[0]);
        return 1;
    }
    
    char *endptr;
    long val_l = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val_l <= 0 || val_l > INT_MAX || errno == ERANGE) {
        fprintf(stderr, "Length must be a positive integer within valid range.\n");
        return 1;
    }
    int k = (int)val_l;
    
    int n = argc - 2;
    int *values = (int *)malloc(n * sizeof(int));
    if (values == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }
    
    for (int i = 0; i < n; i++) {
        val_l = strtol(argv[i + 2], &endptr, 10);
        if (*endptr != '\0' || val_l < INT_MIN || val_l > INT_MAX || errno == ERANGE) {
            fprintf(stderr, "Value must be an integer within valid range.\n");
            free(values);
            return 1;
        }
        values[i] = (int)val_l;
    }
    
    long long result = count_sequences(values, n, k, 0, 0);
    printf("%lld\n", result);
    
    free(values);
    return 0;
}