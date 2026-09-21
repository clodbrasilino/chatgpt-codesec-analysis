#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int count_digits(long long n) {
    int count = 0;
    
    if (n == 0) {
        return 1;
    }
    
    if (n == LLONG_MIN) {
        n = LLONG_MAX;
    } else if (n < 0) {
        n = -n;
    }
    
    while (n > 0) {
        count++;
        n /= 10;
    }
    
    return count;
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 'num' is assigned a value that is never used. [unreadVariable]
     *  The scope of the variable 'num' can be reduced. [variableScope]
     */
    long long num = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        char *endptr;
        num = strtoll(buffer, &endptr, 10);
        
        if (endptr == buffer) {
            return 1;
        }
        
        int digits = count_digits(num);
        printf("%d\n", digits);
    } else {
        return 1;
    }
    
    return 0;
}