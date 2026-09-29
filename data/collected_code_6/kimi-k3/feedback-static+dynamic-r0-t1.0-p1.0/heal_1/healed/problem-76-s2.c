#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

long long count_squares(long long m, long long n) {
    if (m <= 0 || n <= 0) {
        return 0;
    }
    
    if (m < n) {
        long long temp = m;
        m = n;
        n = temp;
    }
    
    if (n > 2097151 || m > 3037000499LL) {
        return 0;
    }
    
    unsigned long long um = (unsigned long long)m;
    unsigned long long un = (unsigned long long)n;
    
    unsigned long long term1 = un;
    unsigned long long term2 = un + 1;
    unsigned long long term3 = 3 * um - un + 1;
    
    if (term1 % 2 == 0) {
        term1 /= 2;
    } else if (term2 % 2 == 0) {
        term2 /= 2;
    } else {
        term3 /= 2;
    }
    
    if (term1 % 3 == 0) {
        term1 /= 3;
    } else if (term2 % 3 == 0) {
        term2 /= 3;
    } else {
        term3 /= 3;
    }
    
    unsigned long long result = term1 * term2 * term3;
    
    if (result > 9223372036854775807ULL) {
        return 0;
    }
    
    return (long long)result;
}

int main(void) {
    long long m, n;
    
    if (scanf("%lld %lld", &m, &n) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", count_squares(m, n));
    
    return EXIT_SUCCESS;
}