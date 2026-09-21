#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

unsigned long long lucas(int n) {
    if (n == 0) return 2;
    if (n == 1) return 1;
    
    unsigned long long prev = 2;
    unsigned long long curr = 1;
    int i;
    
    for (i = 2; i <= n; i++) {
        if (ULLONG_MAX - curr < prev) {
            return 0;
        }
        unsigned long long next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *endptr;
    long val;
    int n;
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    errno = 0;
    val = strtol(input, &endptr, 10);
    
    if (errno != 0 || endptr == input || val < 0 || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    
    while (*endptr == ' ' || *endptr == '\t' || *endptr == '\n' || *endptr == '\r') {
        endptr++;
    }
    
    if (*endptr != '\0') {
        return EXIT_FAILURE;
    }
    
    n = (int)val;
    printf("%llu\n", lucas(n));
    
    return EXIT_SUCCESS;
}