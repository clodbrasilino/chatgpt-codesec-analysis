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
    /* Possible weaknesses found:
     *  Variable 'newline_found' is assigned a value that is never used. [unreadVariable]
     *  The scope of the variable 'newline_found' can be reduced. [variableScope]
     */
    int newline_found = 0;
    /* Possible weaknesses found:
     *  Variable 'c' is assigned a value that is never used. [unreadVariable]
     */
    int c = 0;
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    input[sizeof(input) - 1] = '\0';
    
    len = strnlen(input, sizeof(input));
    
    if (len == sizeof(input) - 1 && input[len - 1] != '\n') {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        return EXIT_FAILURE;
    }
    
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        /* Possible weaknesses found:
         *  Variable 'newline_found' is assigned a value that is never used. [unreadVariable]
         *  Value stored to 'newline_found' is never read [deadcode.DeadStores]
         */
        newline_found = 1;
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