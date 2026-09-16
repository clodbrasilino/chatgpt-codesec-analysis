#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

unsigned long long delannoy(int n) {
    if (n < 0) {
        return 0;
    }
    
    if (n == 0) {
        return 1;
    }
    
    unsigned long long *prev = malloc((size_t)(n + 1) * sizeof(unsigned long long));
    unsigned long long *curr = malloc((size_t)(n + 1) * sizeof(unsigned long long));
    
    if (prev == NULL || curr == NULL) {
        free(prev);
        free(curr);
        return 0;
    }
    
    for (int j = 0; j <= n; j++) {
        prev[j] = 1;
    }
    
    for (int i = 1; i <= n; i++) {
        curr[0] = 1;
        for (int j = 1; j <= n; j++) {
            curr[j] = curr[j - 1] + prev[j] + prev[j - 1];
        }
        unsigned long long *temp = prev;
        prev = curr;
        curr = temp;
    }
    
    unsigned long long result = prev[n];
    
    free(prev);
    free(curr);
    
    return result;
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *endptr;
    errno = 0;
    long n = strtol(argv[1], &endptr, 10);
    
    if (errno != 0 || endptr == argv[1] || *endptr != '\0' || n < 0 || n > INT_MAX) {
        fprintf(stderr, "Invalid input: must be a non-negative integer\n");
        return EXIT_FAILURE;
    }
    
    unsigned long long result = delannoy((int)n);
    printf("%llu\n", result);
    
    return EXIT_SUCCESS;
}