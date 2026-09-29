#include <stdio.h>
#include <stdlib.h>

int count_digits(long long number) {
    int count = 0;
    
    if (number == 0) {
        return 1;
    }
    
    if (number < 0) {
        /* Possible weaknesses found:
         * UBSan: negation of -9223372036854775808 cannot be represented in type 'long long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000000,sig:06,src:000009,time:46144,execs:19072,op:havoc,rep:6)
         */
        number = -number;
    }
    
    while (number != 0) {
        number /= 10;
        count++;
    }
    
    return count;
}

int main(void) {
    long long number;
    int result;
    
    printf("Enter a number: ");
    
    if (scanf("%lld", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    result = count_digits(number);
    printf("Number of digits: %d\n", result);
    
    return EXIT_SUCCESS;
}