#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int sum_even_index_binomial(int n, long long *result) {
    if (result == NULL || n < 0) {
        return -1;
    }
    
    if (n == 0) {
        *result = 1;
        return 0;
    }
    
    if (n >= (int)(sizeof(long long) * CHAR_BIT)) {
        return -1;
    }
    
    *result = 1LL << (n - 1);
    return 0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[64];
    char *endptr;
    long val;
    long long sum;
    int n;
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    if (sizeof(input) > 0 && input[sizeof(input) - 1] != '\0') {
        return EXIT_FAILURE;
    }
    
    errno = 0;
    val = strtol(input, &endptr, 10);
    
    if (errno != 0 || endptr == input || (*endptr != '\n' && *endptr != '\0')) {
        return EXIT_FAILURE;
    }
    
    if (val < 0 || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    
    n = (int)val;
    
    if (sum_even_index_binomial(n, &sum) != 0) {
        return EXIT_FAILURE;
    }
    
    if (printf("%lld\n", sum) < 0) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}