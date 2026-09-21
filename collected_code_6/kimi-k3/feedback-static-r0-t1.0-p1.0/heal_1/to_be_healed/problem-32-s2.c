#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

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
    uint64_t num;
    
    printf("Enter a positive integer: ");
    
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu64, &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    uint64_t result = largest_prime_factor(num);
    
    if (result == 0) {
        printf("No prime factors exist for numbers less than 2\n");
    } else {
        printf("Largest prime factor: %" PRIu64 "\n", result);
    }
    
    return 0;
}