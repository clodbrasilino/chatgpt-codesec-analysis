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
    char input[128];
    char *endptr;
    long long num;
    long long result;
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    if (strchr(input, '\n') == NULL) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
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