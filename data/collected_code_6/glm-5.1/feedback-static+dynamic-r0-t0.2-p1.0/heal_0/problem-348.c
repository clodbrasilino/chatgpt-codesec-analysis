#include <stdio.h>
#include <stdlib.h>

int count_sequences(int *values, int n, int k, int current_sum, int depth) {
    if (depth == k) {
        return 1;
    }
    int total = 0;
    for (int i = 0; i < n; i++) {
        int next_sum = current_sum + values[i];
        if (next_sum >= 0) {
            total += count_sequences(values, n, k, next_sum, depth + 1);
        }
    }
    return total;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <length> <value1> <value2> ...\n", argv[0]);
        return 1;
    }
    int k = atoi(argv[1]);
    if (k <= 0) {
        fprintf(stderr, "Length must be a positive integer.\n");
        return 1;
    }
    int n = argc - 2;
    if (n <= 0) {
        fprintf(stderr, "At least one value must be provided.\n");
        return 1;
    }
    int *values = (int *)malloc(n * sizeof(int));
    if (values == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        values[i] = atoi(argv[i + 2]);
    }
    int result = count_sequences(values, n, k, 0, 0);
    printf("%d\n", result);
    free(values);
    return 0;
}