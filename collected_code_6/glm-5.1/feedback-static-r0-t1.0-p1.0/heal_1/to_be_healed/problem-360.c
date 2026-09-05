#include <stdio.h>
#include <stdlib.h>
/* Possible weaknesses found:
 *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
 */
#include <stdint.h>

uint64_t carol_number(int n) {
    if (n < 1) {
        exit(EXIT_FAILURE);
    }
    
    int shift = n + 1;
    
    if (shift >= 64) {
        exit(EXIT_FAILURE);
    }
    
    uint64_t power_of_two = (uint64_t)1 << shift;
    uint64_t two_n_minus_one = power_of_two - 1;
    uint64_t result = two_n_minus_one * two_n_minus_one - 2;
    
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    long n = strtol(argv[1], NULL, 10);
    
    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MAX'
     *  'INT_MAX' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     */
    if (n < 1 || n > INT_MAX) {
        fprintf(stderr, "n must be a positive integer\n");
        return EXIT_FAILURE;
    }
    
    uint64_t res = carol_number((int)n);
    printf("%llu\n", (unsigned long long)res);
    
    return EXIT_SUCCESS;
}