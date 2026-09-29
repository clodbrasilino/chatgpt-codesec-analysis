#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

long long sum_of_cubes(long n) {
    if (n > 0 && (unsigned long long)n * n > ULLONG_MAX / n) return 0;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:142,execs:133,op:havoc,rep:2)
     * UBSan: signed integer overflow: 9223372036854775807 * -9223372036854775808 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:142,execs:133,op:havoc,rep:2)
     */
    long long result = (long long)n * (n + 1) / 2;
    if ((unsigned long long)result * result > ULLONG_MAX) return 0;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -4611686018427387904 * -4611686018427387904 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:142,execs:133,op:havoc,rep:2)
     * UBSan: signed integer overflow: 55555611111 * 55555611111 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:452,execs:392,op:havoc,rep:4)
     */
    return result * result;
}

long long sum_of_numbers(long n) {
    if (n > 0 && (unsigned long long)n + 1 > ULLONG_MAX / n) return 0;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 3333333333 * 3333333334 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:589,execs:509,op:havoc,rep:2)
     */
    return (long long)n * (n + 1) / 2;
}

long long difference(long n) {
    long long cubes = sum_of_cubes(n);
    long long numbers = sum_of_numbers(n);
    if (cubes < 0 || numbers < 0) return 0;
    return cubes - numbers;
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