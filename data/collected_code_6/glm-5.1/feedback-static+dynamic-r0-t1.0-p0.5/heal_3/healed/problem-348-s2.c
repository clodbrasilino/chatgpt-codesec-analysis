#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

int count_sequences(const int *values, int n, int k, int current_sum, int current_len) {
    if (current_sum < 0) {
        return 0;
    }
    if (current_len == k) {
        return 1;
    }
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += count_sequences(values, n, k, current_sum + values[i], current_len + 1);
    }
    return total;
}

static int safe_strtoi(const char *str, int *out) {
    char *endptr;
    long val;
    errno = 0;
    val = strtol(str, &endptr, 10);
    if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
        return -1;
    }
    if (endptr == str || *endptr != '\0') {
        return -1;
    }
    *out = (int)val;
    return 0;
}

int main(int argc, char * const * const argv) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <sequence_length> <value1> <value2> ...\n", argv[0]);
        return 1;
    }
    int k;
    if (safe_strtoi(argv[1], &k) != 0 || k <= 0) {
        fprintf(stderr, "Sequence length must be a positive integer within valid range.\n");
        return 1;
    }
    int n = argc - 2;
    int *values = (int *)malloc(n * sizeof(int));
    if (values == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        if (safe_strtoi(argv[i + 2], &values[i]) != 0) {
            fprintf(stderr, "Invalid integer value or out of range: %s\n", argv[i + 2]);
            free(values);
            return 1;
        }
    }
    int result = count_sequences(values, n, k, 0, 0);
    printf("%d\n", result);
    free(values);
    return 0;
}