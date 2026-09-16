#include <stdio.h>
#include <stdlib.h>

unsigned long long count_binary_sequences(int n) {
    if (n <= 0) {
        return 0;
    }
    
    int max_sum = n;
    int array_size = max_sum + 1;
    
    unsigned long long *current = (unsigned long long *)calloc(array_size, sizeof(unsigned long long));
    unsigned long long *next = (unsigned long long *)calloc(array_size, sizeof(unsigned long long));
    
    if (current == NULL || next == NULL) {
        free(current);
        free(next);
        return 0;
    }
    
    current[0] = 1;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= max_sum; j++) {
            next[j] = 0;
        }
        
        for (int j = 0; j <= i; j++) {
            if (current[j] > 0) {
                next[j] += current[j];
                next[j + 1] += current[j];
            }
        }
        
        unsigned long long *temp = current;
        current = next;
        next = temp;
    }
    
    unsigned long long total = 0;
    for (int sum = 0; sum <= max_sum; sum++) {
        total += current[sum] * current[sum];
    }
    
    free(current);
    free(next);
    
    return total;
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
    
    unsigned long long result = count_binary_sequences(n);
    printf("Count: %llu\n", result);
    
    return EXIT_SUCCESS;
}