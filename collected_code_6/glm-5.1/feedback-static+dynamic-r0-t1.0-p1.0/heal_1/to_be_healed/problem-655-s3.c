#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long sum_fifth_power(int n) {
    if (n < 0) {
        return 0;
    }
    
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        if (sum > LLONG_MAX - (long long)i * i * i * i * i) {
            return 0;
        }
        sum += (long long)i * i * i * i * i;
    }
    
    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int n;
    
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    
    long long val = strtoll(argv[1], NULL, 10);
    if (val < 0 || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    
    n = (int)val;
    
    long long result = sum_fifth_power(n);
    
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}