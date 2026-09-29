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
     *  The scope of the variable 'num' can be reduced. [variableScope]
     *  Variable 'num' is assigned a value that is never used. [unreadVariable]
     */
    long long num = 0;
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