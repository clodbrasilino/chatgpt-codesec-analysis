#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int64_t find_carol_number(int n) {
    if (n < 1 || n > 31) {
        return -2;
    }
    int64_t power_of_two = 1LL << n;
    int64_t term = power_of_two - 1;
    return (term * term) - 2;
}

int main(void) {
    int n = 4;
    int64_t result = find_carol_number(n);
    
    if (result == -2) {
        fprintf(stderr, "Invalid input bounds\n");
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", (long long)result);
    
    return EXIT_SUCCESS;
}