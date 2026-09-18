#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 7, got <no output>
  *  test case 0 failed: expected 5, got <no output>
  *  test case 1 failed: expected 8, got <no output>
  */

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
    char buffer[256];
    
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        char *endptr;
        long long num = strtoll(buffer, &endptr, 10);
        
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