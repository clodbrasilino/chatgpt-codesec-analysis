#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

long long find_nth_non_multiple(long long n, long long divisor) {
    if (n <= 0 || divisor == 0) {
        errno = EINVAL;
        return -1;
    }
    
    /* Possible weaknesses found:
     * UBSan: negation of -9223372036854775808 cannot be represented in type 'long long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000000,sig:06,src:000007,time:9291,execs:4163,op:havoc,rep:3)
     */
    long long abs_divisor = llabs(divisor);
    if (abs_divisor == 1) {
        errno = EDOM;
        return -1;
    }
    
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -9223372036854775808 - 1 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000007,time:9291,execs:4163,op:havoc,rep:3)
     */
    if (n > LLONG_MAX - (n - 1) / (abs_divisor - 1)) {
        errno = ERANGE;
        return -1;
    }
    
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -9223372036854775808 - 1 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000007,time:9291,execs:4163,op:havoc,rep:3)
     */
    long long result = n + (n - 1) / (abs_divisor - 1);
    
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