#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long sum_fifth_power(int n) {
    if (n < 0) {
        return 0;
    }
    
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        long long term = (long long)i * i * i * i * i;
        if (sum > LLONG_MAX - term) {
            return 0;
        }
        sum += term;
    }
    
    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    int n;
    
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    
    char *endptr;
    long long val = strtoll(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < 0 || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    
    n = (int)val;
    
    long long result = sum_fifth_power(n);
    
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}