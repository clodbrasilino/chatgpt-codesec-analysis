#include <stdio.h>
#include <stdlib.h>

int countDigits(long long num) {
    int count = 0;
    if (num == 0) {
        return 1;
    }
    if (num < 0) {
        /* Possible weaknesses found:
         * UBSan: negation of -9223372036854775808 cannot be represented in type 'long long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000000,sig:06,src:000002,time:24036,execs:9819,op:havoc,rep:10)
         */
        num = -num;
    }
    while (num > 0) {
        num /= 10;
        count++;
    }
    return count;
}

int hasSameDigits(long long num1, long long num2) {
    return countDigits(num1) == countDigits(num2);
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000015,time:37353,execs:15587,op:havoc,rep:4; likely memory-safety defect
  */

int main(void) {
    long long num1, num2;
    
    if (scanf("%lld %lld", &num1, &num2) != 2) {
        return EXIT_FAILURE;
    }
    
    if (hasSameDigits(num1, num2)) {
        printf("Same number of digits\n");
    } else {
        printf("Different number of digits\n");
    }
    
    return EXIT_SUCCESS;
}