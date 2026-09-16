#include <stdio.h>
#include <stdlib.h>

unsigned long long nCr(int n, int r) {
    if (r > n) return 0;
    if (r == 0 || r == n) return 1;
    if (r > n - r) r = n - r;
    
    unsigned long long result = 1;
    for (int i = 0; i < r; i++) {
        result = result * (n - i) / (i + 1);
    }
    return result;
}

unsigned long long derangement(int n) {
    if (n == 0) return 1;
    if (n == 1) return 0;
    
    unsigned long long *dp = (unsigned long long *)malloc((n + 1) * sizeof(unsigned long long));
    if (dp == NULL) {
        return 0;
    }
    
    dp[0] = 1;
    dp[1] = 0;
    
    for (int i = 2; i <= n; i++) {
        dp[i] = (i - 1) * (dp[i - 1] + dp[i - 2]);
    }
    
    unsigned long long result = dp[n];
    free(dp);
    return result;
}

unsigned long long rencontres_number(int n) {
    if (n < 0) return 0;
    
    unsigned long long sum = 0;
    for (int k = 0; k <= n; k++) {
        sum += nCr(n, k) * derangement(n - k);
    }
    return sum;
}

int main(void) {
    int n;
    
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        fprintf(stderr, "n must be non-negative\n");
        return EXIT_FAILURE;
    }
    
    printf("R(%d) = %llu\n", n, rencontres_number(n));
    
    return EXIT_SUCCESS;
}