#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

uint64_t largest_prime_factor(uint64_t n) {
    uint64_t largest = 0;
    
    if (n < 2) {
        return 0;
    }
    
    while (n % 2 == 0) {
        largest = 2;
        n /= 2;
    }
    
    for (uint64_t i = 3; i <= n / i; i += 2) {
        while (n % i == 0) {
            largest = i;
            n /= i;
        }
    }
    
    if (n > 1) {
        largest = n;
    }
    
    return largest;
}

int main(void) {
    char buffer[256];
    char *endptr;
    unsigned long long num;
    
    printf("Enter a positive integer: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    errno = 0;
    num = strtoull(buffer, &endptr, 10);
    
    if (errno == ERANGE || endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (num > UINT64_MAX) {
        fprintf(stderr, "Number too large\n");
        return 1;
    }
    
    uint64_t result = largest_prime_factor((uint64_t)num);
    
    if (result == 0) {
        printf("No prime factors exist for numbers less than 2\n");
    } else {
        printf("Largest prime factor: %" PRIu64 "\n", result);
    }
    
    return 0;
}