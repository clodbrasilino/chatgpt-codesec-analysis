#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

int count_primes(int n)
{
    if (n <= 2) {
        return 0;
    }
    
    bool *is_prime = malloc((size_t)n * sizeof(*is_prime));
    if (is_prime == NULL) {
        return -1;
    }
    
    for (int i = 0; i < n; i++) {
        is_prime[i] = true;
    }
    is_prime[0] = false;
    is_prime[1] = false;
    
    int count = 0;
    for (int i = 2; i < n; i++) {
        if (is_prime[i]) {
            count++;
            if (i <= (n - 1) / i) {
                for (int j = i * i; j < n; j += i) {
                    is_prime[j] = false;
                }
            }
        }
    }
    
    free(is_prime);
    return count;
}

int main(void)
{
    int n;
    
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        fprintf(stderr, "Input must be non-negative\n");
        return EXIT_FAILURE;
    }
    
    int result = count_primes(n);
    if (result < 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    printf("%d\n", result);
    return EXIT_SUCCESS;
}