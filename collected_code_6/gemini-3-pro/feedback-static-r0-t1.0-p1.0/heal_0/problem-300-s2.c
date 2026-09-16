#include <stdio.h>
#include <stdlib.h>

unsigned long long calculate_combinations(int n, int k) {
    if (k < 0 || k > n) {
        return 0;
    }
    if (k == 0 || k == n) {
        return 1;
    }
    if (k > n / 2) {
        k = n - k;
    }
    
    unsigned long long result = 1;
    for (int i = 1; i <= k; i++) {
        result = result * (n - i + 1);
        result = result / i;
    }
    
    return result;
}

unsigned long long count_binary_sequences(int n) {
    if (n < 0) {
        return 0;
    }
    
    unsigned long long total_count = 0;
    
    for (int k = 0; k <= n; k++) {
        unsigned long long c = calculate_combinations(n, k);
        total_count += c * c;
    }
    
    return total_count;
}

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0 || n > 30) {
        fprintf(stderr, "Input out of supported range (0-30 to avoid overflow)\n");
        return EXIT_FAILURE;
    }
    
    unsigned long long result = count_binary_sequences(n);
    printf("%llu\n", result);
    
    return EXIT_SUCCESS;
}