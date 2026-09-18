#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

long long find_nth_non_multiple(long long n, long long divisor) {
    if (n <= 0 || divisor == 0) {
        errno = EINVAL;
        return -1;
    }
    
    unsigned long long abs_divisor;
    if (divisor == LLONG_MIN) {
        abs_divisor = (unsigned long long)LLONG_MAX + 1ULL;
    } else {
        abs_divisor = (unsigned long long)llabs(divisor);
    }
    
    if (abs_divisor == 1) {
        errno = EDOM;
        return -1;
    }
    
    unsigned long long un = (unsigned long long)n;
    unsigned long long divisor_minus_one = abs_divisor - 1ULL;
    unsigned long long quotient = (un - 1ULL) / divisor_minus_one;
    
    if (un > (unsigned long long)LLONG_MAX - quotient) {
        errno = ERANGE;
        return -1;
    }
    
    long long result = (long long)(un + quotient);
    
    if (divisor < 0) {
        if (result == LLONG_MIN) {
            errno = ERANGE;
            return -1;
        }
        result = -result;
    }
    
    return result;
}

int main(void) {
    long long n, divisor, result;
    
    printf("Enter n: ");
    if (scanf("%lld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter divisor: ");
    if (scanf("%lld", &divisor) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    result = find_nth_non_multiple(n, divisor);
    
    if (result == -1 && errno != 0) {
        fprintf(stderr, "Error: %s\n", 
                errno == EINVAL ? "Invalid arguments" :
                errno == EDOM ? "Divisor magnitude must be greater than 1" :
                "Result overflow");
        return EXIT_FAILURE;
    }
    
    printf("Result: %lld\n", result);
    return EXIT_SUCCESS;
}