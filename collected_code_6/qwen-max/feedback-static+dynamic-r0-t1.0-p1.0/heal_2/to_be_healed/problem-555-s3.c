#include <stdio.h>
#include <stdint.h>

long long sum_of_cubes(long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 * -9223372036854775808 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:129,execs:130,op:havoc,rep:2)
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:129,execs:130,op:havoc,rep:2)
     * UBSan: signed integer overflow: 3333333333333333333 * 3333333333333333334 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:1320,execs:1239,op:havoc,rep:1)
     */
    long long result = (n * (n + 1) / 2);
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 55889444611 * 55889444611 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:2018,execs:1880,op:havoc,rep:5)
     * UBSan: signed integer overflow: -4611686018427387904 * -4611686018427387904 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:129,execs:130,op:havoc,rep:2)
     * UBSan: signed integer overflow: -3505532041302085177 * -3505532041302085177 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:1320,execs:1239,op:havoc,rep:1)
     */
    return result * result;
}

long long sum_of_numbers(long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 * -9223372036854775808 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:129,execs:130,op:havoc,rep:2)
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:129,execs:130,op:havoc,rep:2)
     * UBSan: signed integer overflow: 3333333333333333333 * 3333333333333333334 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:1320,execs:1239,op:havoc,rep:1)
     */
    return (n * (n + 1)) / 2;
}

long long difference(long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 7873908936983791793 - -3505532041302085177 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:1320,execs:1239,op:havoc,rep:1)
     */
    return sum_of_cubes(n) - sum_of_numbers(n);
}

int main() {
    long n;
    printf("Enter a natural number: ");
    if (scanf("%ld", &n) != 1 || n < 1) {
        printf("Please enter a valid natural number.\n");
        return 1;
    }

    long long diff = difference(n);
    printf("The difference is: %lld\n", diff);
    return 0;
}