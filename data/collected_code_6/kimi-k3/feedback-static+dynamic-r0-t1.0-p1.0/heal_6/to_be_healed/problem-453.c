#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

long long sum_even_factors(long long n) {
    long long sum = 0;
    long long abs_n;
    long long i;
    
    if (n == 0) {
        return 0;
    }
    
    abs_n = (n < 0) ? -n : n;
    
    for (i = 2; i <= abs_n / 2; i += 2) {
        if (abs_n % i == 0) {
            sum += i;
        }
    }
    
    if (abs_n % 2 == 0) {
        sum += abs_n;
    }
    
    return sum;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[64];
    char *endptr;
    long long num;
    long long result;
    size_t len;
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    len = strnlen(input, sizeof(input));
    
    if (len == sizeof(input)) {
        return EXIT_FAILURE;
    }
    
    errno = 0;
    num = strtoll(input, &endptr, 10);
    
    if (errno == ERANGE || endptr == input) {
        return EXIT_FAILURE;
    }
    
    if (num == LLONG_MIN) {
        return EXIT_FAILURE;
    }
    
    result = sum_even_factors(num);
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}