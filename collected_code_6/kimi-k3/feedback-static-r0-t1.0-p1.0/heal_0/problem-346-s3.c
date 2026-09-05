#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

unsigned long long entringer(int n, int k) {
    if (n < 0 || k < 0 || k > n) {
        return 0;
    }
    
    if (k == 0) {
        return (n == 0) ? 1 : 0;
    }
    
    if (n == 0) {
        return 0;
    }
    
    unsigned long long *prev = calloc((size_t)n + 1, sizeof(unsigned long long));
    unsigned long long *curr = calloc((size_t)n + 1, sizeof(unsigned long long));
    
    if (prev == NULL || curr == NULL) {
        free(prev);
        free(curr);
        return 0;
    }
    
    prev[0] = 1;
    
    for (int i = 1; i <= n; i++) {
        curr[0] = 0;
        for (int j = 1; j <= i; j++) {
            if (prev[j-1] > ULLONG_MAX - curr[j-1]) {
                free(prev);
                free(curr);
                return 0;
            }
            curr[j] = curr[j-1] + prev[j-1];
        }
        
        unsigned long long *temp = prev;
        prev = curr;
        curr = temp;
        
        for (int j = 0; j <= n; j++) {
            curr[j] = 0;
        }
    }
    
    unsigned long long result = prev[k];
    free(prev);
    free(curr);
    
    return result;
}

int main(void) {
    int n, k;
    
    printf("Enter n and k: ");
    
    if (scanf("%d %d", &n, &k) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0 || k < 0) {
        fprintf(stderr, "n and k must be non-negative\n");
        return EXIT_FAILURE;
    }
    
    if (k > n) {
        fprintf(stderr, "k must be less than or equal to n\n");
        return EXIT_FAILURE;
    }
    
    unsigned long long result = entringer(n, k);
    printf("E(%d, %d) = %llu\n", n, k, result);
    
    return EXIT_SUCCESS;
}