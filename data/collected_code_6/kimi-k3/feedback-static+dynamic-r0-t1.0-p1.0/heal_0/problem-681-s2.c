#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <errno.h>

int smallest_prime_divisor(uint64_t n, uint64_t *result) {
    if (result == NULL || n < 2) {
        return -1;
    }
    
    if (n % 2 == 0) {
        *result = 2;
        return 0;
    }
    
    for (uint64_t i = 3; i <= n / i; i += 2) {
        if (n % i == 0) {
            *result = i;
            return 0;
        }
    }
    
    *result = n;
    return 0;
}

int main(void) {
    uint64_t number;
    uint64_t divisor;
    char buffer[64];
    
    printf("Enter a positive integer (>= 2): ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    errno = 0;
    char *endptr;
    unsigned long long temp = strtoull(buffer, &endptr, 10);
    
    if (errno != 0 || endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    number = (uint64_t)temp;
    
    if (smallest_prime_divisor(number, &divisor) != 0) {
        fprintf(stderr, "Number must be >= 2\n");
        return 1;
    }
    
    printf("Smallest prime divisor of %llu is %llu\n", 
           (unsigned long long)number, (unsigned long long)divisor);
    
    return 0;
}