#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

long long sum_of_cubes(long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 333333333333 * 333333333333 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:110,execs:126,op:havoc,rep:1)
     */
    if (n > 0 && n * n > LLONG_MAX / n) return 0;
    long long result = (n * (n + 1) / 2);
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 6172882716 * 6172882716 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000004,time:329,execs:338,op:quick,pos:6)
     */
    if (result * result > LLONG_MAX) return 0;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 6172882716 * 6172882716 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000004,time:329,execs:338,op:quick,pos:6)
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