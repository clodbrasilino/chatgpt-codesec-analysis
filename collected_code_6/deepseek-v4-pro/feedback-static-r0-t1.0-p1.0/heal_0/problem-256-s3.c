#include <stdio.h>
#include <stdbool.h>

int count_primes(int n) {
    if (n <= 2) return 0;
    
    bool *is_prime = (bool*)malloc(n * sizeof(bool));
    if (is_prime == NULL) return -1;
    
    for (int i = 2; i < n; i++) {
        is_prime[i] = true;
    }
    
    for (int i = 2; i * i < n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j < n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    
    int count = 0;
    for (int i = 2; i < n; i++) {
        if (is_prime[i]) count++;
    }
    
    free(is_prime);
    return count;
}

int main() {
    printf("%d\n", count_primes(10));
    printf("%d\n", count_primes(0));
    printf("%d\n", count_primes(1));
    printf("%d\n", count_primes(2));
    printf("%d\n", count_primes(100));
    
    return 0;
}