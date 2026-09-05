#include <stdio.h>
#include <stdlib.h>

int is_prime(int num) {
    if (num <= 1) {
        return 0;
    }
    if (num == 2) {
        return 1;
    }
    if (num % 2 == 0) {
        return 0;
    }
    for (int i = 3; i * i <= num; i += 2) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}

long long sum_of_primes(int n) {
    if (n < 2) {
        return 0;
    }
    long long sum = 0;
    for (int i = 2; i <= n; i++) {
        if (is_prime(i)) {
            sum += i;
        }
    }
    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    
    if (endptr == argv[1] || *endptr != '\0' || val < 1 || val > 2147483647) {
        return EXIT_FAILURE;
    }
    
    int n = (int)val;
    long long result = sum_of_primes(n);
    
    int ret = printf("%lld\n", result);
    if (ret < 0) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}