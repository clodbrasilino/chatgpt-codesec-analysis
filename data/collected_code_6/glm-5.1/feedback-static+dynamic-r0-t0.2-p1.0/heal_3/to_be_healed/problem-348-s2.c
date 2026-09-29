#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int count_sequences(const int *values, int n, int k, int current_sum, int depth) {
    if (current_sum < 0) {
        return 0;
    }
    if (depth == k) {
        return 1;
    }
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += count_sequences(values, n, k, current_sum + values[i], depth + 1);
    }
    return total;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <sequence_length> <value1> <value2> ...\n", argv[0]);
        return 1;
    }
    
    errno = 0;
    char *endptr;
    long k_long = strtol(argv[1], &endptr, 10);
    if (errno != 0 || endptr == argv[1] || *endptr != '\0' || k_long <= 0 || k_long > INT_MAX) {
        fprintf(stderr, "Sequence length must be a positive integer within valid range.\n");
        return 1;
    }
    int k = (int)k_long;
    
    int n = argc - 2;
    
    int *values = (int *)malloc((size_t)n * sizeof(int));
    if (values == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        errno = 0;
        long val_long = strtol(argv[i + 2], &endptr, 10);
        if (errno != 0 || endptr == argv[i + 2] || *endptr != '\0' || val_long < INT_MIN || val_long > INT_MAX) {
            fprintf(stderr, "Invalid value provided. Must be a valid integer.\n");
            free(values);
            return 1;
        }
        values[i] = (int)val_long;
    }
    
    int result = count_sequences(values, n, k, 0, 0);
    printf("%d\n", result);
    
    free(values);
    return 0;
}