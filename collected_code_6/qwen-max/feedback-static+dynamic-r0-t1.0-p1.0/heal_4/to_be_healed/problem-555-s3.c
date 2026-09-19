#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

long long sum_of_cubes(long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2222222222222222 * 2222222222222222 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:222,execs:207,op:havoc,rep:3)
     */
    if (n > 0 && n * n > LLONG_MAX / n) return 0;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2222222222222222 * 2222222222222223 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:222,execs:207,op:havoc,rep:3)
     */
    long long result = (n * (n + 1) / 2);
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 55555611111 * 55555611111 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:125,execs:125,op:havoc,rep:4)
     * UBSan: signed integer overflow: -1127972720512597207 * -1127972720512597207 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:222,execs:207,op:havoc,rep:3)
     */
    if (result * result > LLONG_MAX) return 0;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 55555611111 * 55555611111 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:125,execs:125,op:havoc,rep:4)
     * UBSan: signed integer overflow: -1127972720512597207 * -1127972720512597207 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:222,execs:207,op:havoc,rep:3)
     */
    return result * result;
}

long long sum_of_numbers(long n) {
    if (n > 0 && n + 1 > LLONG_MAX / n) return 0;
    return (n * (n + 1)) / 2;
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