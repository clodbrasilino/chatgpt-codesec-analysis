#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    int limit = (int)sqrt(n);
    for (int i = 5; i <= limit; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int count_primes(int n) {
    int count = 0;
    for (int i = 2; i < n; i++) {
        if (is_prime(i)) {
            count++;
        }
    }
    return count;
}

int main(void) {
    int test_values[] = {0, 1, 2, 10, 100, 1000, 10000};
    int num_tests = sizeof(test_values) / sizeof(test_values[0]);
    
    for (int i = 0; i < num_tests; i++) {
        int n = test_values[i];
        int result = count_primes(n);
        printf("count_primes(%d) = %d\n", n, result);
    }
    
    return 0;
}