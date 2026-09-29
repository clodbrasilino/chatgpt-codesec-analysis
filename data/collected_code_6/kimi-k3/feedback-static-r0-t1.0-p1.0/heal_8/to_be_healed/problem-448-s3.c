#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

long long perrin_sum(int n) {
    if (n < 0) {
        return -1;
    }
    
    if (n == 0) {
        return 3;
    }
    if (n == 1) {
        return 3;
    }
    if (n == 2) {
        return 5;
    }
    
    long long p0 = 3;
    long long p1 = 0;
    long long p2 = 2;
    long long sum = 5;
    int i = 0;
    
    for (i = 3; i <= n; i++) {
        long long p_next;
        
        if (p0 > LLONG_MAX - p1) {
            return -1;
        }
        p_next = p0 + p1;
        
        if (sum > LLONG_MAX - p_next) {
            return -1;
        }
        sum += p_next;
        
        p0 = p1;
        p1 = p2;
        p2 = p_next;
    }
    
    return sum;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[64] = {0};
    char *endptr = NULL;
    long val = 0;
    int n = 0;
    long long result = 0;
    size_t len = 0;
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
    
    errno = 0;
    val = strtol(input, &endptr, 10);
    
    if (errno != 0 || endptr == input || *endptr != '\0') {
        return EXIT_FAILURE;
    }
    
    if (val < 0 || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    
    n = (int)val;
    result = perrin_sum(n);
    
    if (result < 0) {
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}