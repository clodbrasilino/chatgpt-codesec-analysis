#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_difference_of_squares(long long n) {
    /* Possible weaknesses found:
     * UBSan: negation of -9223372036854775808 cannot be represented in type 'long long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000000,sig:06,src:000004,time:31587,execs:15271,op:havoc,rep:6)
     */
    long long abs_n = llabs(n);
    if (abs_n % 4 != 2) {
        return true;
    }
    return false;
}

int main(void) {
    long long num = 0;
    
    if (scanf("%lld", &num) != 1) {
        return 1;
    }
    
    if (is_difference_of_squares(num)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    
    return 0;
}