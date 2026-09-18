#include <stdio.h>
#include <stdint.h>

int64_t gcd(int64_t a, int64_t b) {
    while (b != 0) {
        int64_t t = b;
        b = a % b;
        a = t;
    }
    return a;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 255, got <no output>
  *  test case 2 failed: expected 6, got <no output>
  *  test case 0 failed: expected 12, got <no output>
  */

int64_t lcm(int64_t a, int64_t b) {
    return (a / gcd(a, b)) * b;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:6,execs:15,op:(null),pos:0; likely memory-safety defect
  */

int main() {
    int64_t x, y;
    printf("Enter two positive integers: ");
    /* Possible weaknesses found:
     *  %lld in format string (no. 2) requires 'long long *' but the argument type is 'signed long *'. [invalidScanfArgType_int]
     *  %lld in format string (no. 1) requires 'long long *' but the argument type is 'signed long *'. [invalidScanfArgType_int]
     */
    scanf("%lld %lld", &x, &y);
    if (x > 0 && y > 0) {
        /* Possible weaknesses found:
         *  %lld in format string (no. 3) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
         *  %lld in format string (no. 2) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
         *  %lld in format string (no. 1) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
         */
        printf("LCM of %lld and %lld is %lld\n", x, y, lcm(x, y));
    } else {
        printf("Please enter positive integers.\n");
    }
    return 0;
}