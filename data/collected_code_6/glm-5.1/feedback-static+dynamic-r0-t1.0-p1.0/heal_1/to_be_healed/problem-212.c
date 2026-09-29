#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long sum_of_fourth_powers(unsigned int n) {
    unsigned long long sum = 0;
    for (unsigned int i = 1; i <= n; i++) {
        unsigned long long term = (unsigned long long)i * i * i * i;
        if (sum > ULLONG_MAX - term) {
            return 0;
        }
        sum += term;
    }
    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    unsigned int n;
    
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    
    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);
    if (*endptr != '\0' || val > UINT_MAX) {
        return EXIT_FAILURE;
    }
    
    n = (unsigned int)val;
    
    unsigned long long result = sum_of_fourth_powers(n);
    if (result == 0 && n > 0) {
        return EXIT_FAILURE;
    }
    
    printf("%llu\n", result);
    
    return EXIT_SUCCESS;
}