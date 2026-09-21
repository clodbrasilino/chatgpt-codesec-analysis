#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <limits.h>

int newman_conway(int n, int *memo) {
    if (n < 1) {
        return 0;
    }
    if (n == 1 || n == 2) {
        return 1;
    }
    if (memo[n] != 0) {
        return memo[n];
    }
    int prev = newman_conway(n - 1, memo);
    if (prev >= n || prev < 1) {
        return 0;
    }
    int term1 = newman_conway(prev, memo);
    int term2 = newman_conway(n - prev, memo);
    if (term1 == 0 || term2 == 0) {
        return 0;
    }
    if (term1 > 0 && term2 > 0) {
        if (term1 > INT_MAX - term2) {
            return 0;
        }
        int sum = term1 + term2;
        memo[n] = sum;
        return memo[n];
    }
    return 0;
}

int main(void) {
    int n;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    
    printf("Enter n: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    buffer[strcspn(buffer, "\n")] = 0;
    
    if (sscanf(buffer, "%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (n < 1) {
        fprintf(stderr, "n must be positive\n");
        return 1;
    }
    
    if (n > 1000) {
        fprintf(stderr, "n is too large\n");
        return 1;
    }
    
    int *memo = calloc((size_t)n + 1, sizeof(int));
    if (memo == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    int result = newman_conway(n, memo);
    if (result == 0) {
        fprintf(stderr, "Computation failed\n");
        free(memo);
        return 1;
    }
    
    printf("%d\n", result);
    free(memo);
    return 0;
}