#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long sum_of_products(const int *arr, int n) {
    long long total = 0;
    long long current = 0;
    for (int i = 0; i < n; i++) {
        current = current * arr[i] + arr[i];
        total += current;
    }
    return total;
}

int main(int argc, char * const * argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <elements>\n", argv[0]);
        return 1;
    }
    int n = argc - 1;
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        char *endptr;
        errno = 0;
        long val = strtol(argv[i + 1], &endptr, 10);
        if (endptr == argv[i + 1] || *endptr != '\0' || errno == ERANGE || val > INT_MAX || val < INT_MIN) {
            fprintf(stderr, "Invalid integer argument: %s\n", argv[i + 1]);
            free(arr);
            return 1;
        }
        arr[i] = (int)val;
    }
    long long result = sum_of_products(arr, n);
    printf("%lld\n", result);
    free(arr);
    return 0;
}