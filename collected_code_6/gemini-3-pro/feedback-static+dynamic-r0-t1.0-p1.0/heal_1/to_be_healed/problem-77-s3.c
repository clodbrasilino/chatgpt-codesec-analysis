#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int find_digit_difference(long long num) {
    long long n = num;
    if (n < 0) {
        /* Possible weaknesses found:
         * UBSan: negation of -9223372036854775808 cannot be represented in type 'long long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000000,sig:06,src:000013,time:36158,execs:18642,op:havoc,rep:3)
         */
        n = -n;
    }
    
    int even_sum = 0;
    int odd_sum = 0;
    
    while (n > 0) {
        int digit = n % 10;
        if (digit % 2 == 0) {
            even_sum += digit;
        } else {
            odd_sum += digit;
        }
        n /= 10;
    }
    
    return even_sum - odd_sum;
}

int main() {
    long long num;
    
    if (scanf("%lld", &num) != 1) {
        return EXIT_FAILURE;
    }
    
    int difference = find_digit_difference(num);
    
    printf("%d\n", difference);
    
    return EXIT_SUCCESS;
}