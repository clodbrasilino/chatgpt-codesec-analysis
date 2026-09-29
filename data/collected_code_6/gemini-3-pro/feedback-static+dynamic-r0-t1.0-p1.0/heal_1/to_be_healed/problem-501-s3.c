#include <stdio.h>
#include <stdlib.h>

long long findGCD(long long a, long long b) {
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    long long temp;
    
    if (a < 0) {
        /* Possible weaknesses found:
         * UBSan: negation of -9223372036854775808 cannot be represented in type 'long long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000002,sig:06,src:000009,time:20371,execs:9737,op:havoc,rep:4)
         */
        a = -a;
    }
    if (b < 0) {
        /* Possible weaknesses found:
         * UBSan: negation of -9223372036854775808 cannot be represented in type 'long long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000000,sig:06,src:000010,time:12700,execs:6172,op:havoc,rep:3)
         */
        b = -b;
    }
    
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    
    return a;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000009,time:20335,execs:9720,op:havoc,rep:2; likely memory-safety defect
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