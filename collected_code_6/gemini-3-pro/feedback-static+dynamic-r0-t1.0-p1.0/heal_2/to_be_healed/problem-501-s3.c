#include <stdio.h>
#include <stdlib.h>

long long findGCD(long long a, long long b) {
    if (a < 0) {
        /* Possible weaknesses found:
         * UBSan: negation of -9223372036854775808 cannot be represented in type 'long long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000001,sig:06,src:000013,time:34765,execs:17980,op:havoc,rep:15)
         */
        a = -a;
    }
    if (b < 0) {
        /* Possible weaknesses found:
         * UBSan: negation of -9223372036854775808 cannot be represented in type 'long long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000000,sig:06,src:000001,time:3137,execs:1607,op:havoc,rep:8)
         */
        b = -b;
    }
    
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    
    return a;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000002,sig:06,src:000013,time:56161,execs:29087,op:havoc,rep:4; likely memory-safety defect
  */

int main(void) {
    long long num1, num2, gcd;
    int items_read;

    items_read = scanf("%lld %lld", &num1, &num2);
    
    if (items_read != 2) {
        fprintf(stderr, "Error: Invalid input. Please enter two integers.\n");
        return EXIT_FAILURE;
    }

    if (num1 == 0 && num2 == 0) {
        fprintf(stderr, "Error: GCD of 0 and 0 is undefined.\n");
        return EXIT_FAILURE;
    }

    gcd = findGCD(num1, num2);
    
    printf("%lld\n", gcd);

    return EXIT_SUCCESS;
}