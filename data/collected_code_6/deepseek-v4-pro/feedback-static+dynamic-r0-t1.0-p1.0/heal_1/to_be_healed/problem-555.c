#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 30, got <no output>
  *  test case 2 failed: expected 6, got <no output>
  *  test case 1 failed: expected 210, got <no output>
  */

long long difference(long long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 * -9223372036854775808 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:111,execs:68,op:havoc,rep:8)
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:111,execs:68,op:havoc,rep:8)
     * UBSan: signed integer overflow: 3333333333333 * 3333333333334 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:1750,execs:827,op:havoc,rep:3)
     */
    long long sum_n = n * (n + 1) / 2;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -4240262810275200569 * -4240262810275200569 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:1750,execs:827,op:havoc,rep:3)
     * UBSan: signed integer overflow: -4611686018427387904 * -4611686018427387904 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:111,execs:68,op:havoc,rep:8)
     * UBSan: signed integer overflow: 5555556111111 * 5555556111111 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:254,execs:137,op:havoc,rep:10)
     */
    long long sum_cubes = sum_n * sum_n;
    return sum_cubes - sum_n;
}

int main(void) {
    long long n;
    
    printf("Enter a natural number: ");
    if (scanf("%lld", &n) != 1 || n < 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    printf("Difference: %lld\n", difference(n));
    
    return 0;
}