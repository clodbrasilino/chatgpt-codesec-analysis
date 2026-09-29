#include <stdio.h>

long long sum_of_cubes(long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 140703238996804 * 140703238996805 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:8,execs:15,op:(null),pos:0)
     * UBSan: signed integer overflow: 9223372036854775807 * -9223372036854775808 cannot be represented in type 'long' (AFL crash: id:000002,sig:06,src:000001,time:186,execs:60,op:havoc,rep:9)
     * UBSan: signed integer overflow: 55555611111 * 55555611111 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:59,execs:27,op:havoc,rep:9)
     * UBSan: signed integer overflow: -1362960804861675862 * -1362960804861675862 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:8,execs:15,op:(null),pos:0)
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long' (AFL crash: id:000002,sig:06,src:000001,time:186,execs:60,op:havoc,rep:9)
     * UBSan: signed integer overflow: -4611686018427387904 * -4611686018427387904 cannot be represented in type 'long' (AFL crash: id:000002,sig:06,src:000001,time:186,execs:60,op:havoc,rep:9)
     */
    return (n * (n + 1) / 2) * (n * (n + 1) / 2);
}

long long sum_of_numbers(long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long' (AFL crash: id:000002,sig:06,src:000001,time:186,execs:60,op:havoc,rep:9)
     * UBSan: signed integer overflow: 9223372036854775807 * -9223372036854775808 cannot be represented in type 'long' (AFL crash: id:000002,sig:06,src:000001,time:186,execs:60,op:havoc,rep:9)
     * UBSan: signed integer overflow: 140703238996804 * 140703238996805 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:8,execs:15,op:(null),pos:0)
     */
    return (n * (n + 1)) / 2;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 6, got <no output>
  *  test case 1 failed: expected 210, got <no output>
  *  test case 0 failed: expected 30, got <no output>
  */

long long difference(long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 8459795740078713060 - -1362960804861675862 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:8,execs:15,op:(null),pos:0)
     */
    return sum_of_cubes(n) - sum_of_numbers(n);
}

int main() {
    long n;
    printf("Enter a natural number: ");
    scanf("%ld", &n);

    if (n < 1) {
        printf("Please enter a valid natural number.\n");
        return 1;
    }

    long long diff = difference(n);
    printf("The difference is: %lld\n", diff);
    return 0;
}