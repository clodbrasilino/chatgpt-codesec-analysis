#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>

int64_t *memo;
int64_t memo_size;

int64_t max(int64_t a, int64_t b) {
    return a > b ? a : b;
}

int64_t f(int64_t n) {
    if (n == 0) return 0;
    if (n < 12) return n;
    
    if (memo[n] != -1) return memo[n];
    
    int64_t result = max(n, f(n/2) + f(n/3) + f(n/4) + f(n/5));
    memo[n] = result;
    return result;
}

int main() {
    int64_t n;
    char buffer[32];
    
    printf("Enter a number: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        printf("Error reading input\n");
        return 1;
    }
    
    buffer[strcspn(buffer, "\n")] = '\0';
    
    char *endptr;
    n = strtoimax(buffer, &endptr, 10);
    
    if (*endptr != '\0' || endptr == buffer) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (n < 0) {
        printf("Please enter a non-negative number\n");
        return 1;
    }
    
    if (n == INT64_MAX) {
        printf("Input too large\n");
        return 1;
    }
    
    if (n > (SIZE_MAX / sizeof(int64_t)) - 1) {
        printf("Input too large for memory allocation\n");
        return 1;
    }
    
    memo_size = n + 1;
    memo = (int64_t*)malloc(memo_size * sizeof(int64_t));
    if (memo == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    for (int64_t i = 0; i < memo_size; i++) {
        memo[i] = -1;
    }
    
    int64_t result = f(n);
    printf("Maximum sum: %" PRId64 "\n", result);
    
    free(memo);
    return 0;
}