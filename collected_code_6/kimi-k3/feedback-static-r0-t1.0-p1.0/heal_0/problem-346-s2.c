#include <stdio.h>
#include <stdlib.h>

unsigned long long entringer(int n, int k) {
    if (n < 0 || k < 0 || k >= n) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    
    unsigned long long *prev = (unsigned long long *)calloc((size_t)n, sizeof(unsigned long long));
    unsigned long long *curr = (unsigned long long *)calloc((size_t)n, sizeof(unsigned long long));
    
    if (prev == NULL || curr == NULL) {
        free(prev);
        free(curr);
        return 0;
    }
    
    prev[0] = 1;
    
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            curr[j] = 0;
        }
        
        if (i % 2 == 0) {
            for (int j = 1; j < i; j++) {
                curr[j] = curr[j - 1] + prev[j - 1];
            }
        } else {
            for (int j = i - 2; j >= 0; j--) {
                curr[j] = curr[j + 1] + prev[j];
            }
        }
        
        unsigned long long *temp = prev;
        prev = curr;
        curr = temp;
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
        return 1;
    }
    
    if (n < 1 || k < 0 || k >= n) {
        fprintf(stderr, "Invalid parameters: n must be >= 1 and 0 <= k < n\n");
        return 1;
    }
    
    printf("E(%d, %d) = %llu\n", n, k, entringer(n, k));
    
    return 0;
}