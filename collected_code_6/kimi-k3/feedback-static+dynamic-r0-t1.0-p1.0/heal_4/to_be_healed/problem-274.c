#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

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
    size_t len;
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    if (len == 0) {
        return EXIT_FAILURE;
    }
    
    if (len == sizeof(input) - 1 && input[len - 1] != '\n') {
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