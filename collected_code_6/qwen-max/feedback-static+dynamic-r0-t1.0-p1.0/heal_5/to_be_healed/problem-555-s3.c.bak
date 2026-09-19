#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

long long sum_of_cubes(long n) {
    if (n > 0x1FFFFF || n < -0x1FFFFF) return 0;
    int64_t temp = (n * (n + 1)) / 2;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 55555611111 * 55555611111 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:287,execs:145,op:havoc,rep:1)
     */
    int64_t result = temp * temp;
    if (temp > 0 && result / temp != temp) return 0;
    return result;
}

long long sum_of_numbers(long n) {
    if (n > 0x1FFFFF || n < -0x1FFFFF) return 0;
    int64_t temp = n * (n + 1);
    return temp / 2;
}

long long difference(long n) {
    return sum_of_cubes(n) - sum_of_numbers(n);
}

int main() {
    long n;
    printf("Enter a natural number: ");
    if (scanf("%ld", &n) != 1 || n < 1) {
        printf("Invalid input. Please enter a valid natural number.\n");
        return 1;
    }

    long long diff = difference(n);
    printf("The difference is: %lld\n", diff);
    return 0;
}