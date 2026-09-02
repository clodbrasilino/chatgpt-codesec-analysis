#include <stdio.h>
#include <stdlib.h>

unsigned long long count_binary_sequences(int n) {
    if (n <= 0) {
        return 0;
    }
    
    unsigned long long *counts = (unsigned long long *)calloc(n + 1, sizeof(unsigned long long));
    if (counts == NULL) {
        return 0;
    }
    
    counts[0] = 1;
    
    for (int i = 1; i <= n; i++) {
        for (int j = i; j >= 1; j--) {
            counts[j] += counts[j - 1];
        }
    }
    
    unsigned long long result = 0;
    for (int k = 0; k <= n; k++) {
        result += counts[k] * counts[k];
    }
    
    free(counts);
    return result;
}

int main(void) {
    int n;
    
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (n < 0 || n > 30) {
        fprintf(stderr, "n must be between 0 and 30\n");
        return 1;
    }
    
    unsigned long long result = count_binary_sequences(n);
    printf("%llu\n", result);
    
    return 0;
}