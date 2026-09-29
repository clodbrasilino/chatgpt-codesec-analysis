#include <stdio.h>
#include <stdint.h>

int64_t sum_of_odd_numbers(int64_t l, int64_t r) {
    if (l > r) {
        return 0;
    }

    if (l % 2 == 0) {
        l++;
    }
    if (r % 2 == 0) {
        r--;
    }

    if (l > r) {
        return 0;
    }

    int64_t n = (r - l) / 2 + 1;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 3 + 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000005,time:7873,execs:5031,op:havoc,rep:1)
     * UBSan: signed integer overflow: 2611111111000000000 * 5222222222444444444 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000004,time:3346,execs:2168,op:havoc,rep:3)
     * UBSan: signed integer overflow: 4611686018427387903 * -9223372036854775806 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000005,time:7873,execs:5031,op:havoc,rep:1)
     */
    return n * (l + r) / 2;
}

int main(void) {
    int64_t l, r;
    printf("Enter the range l and r: ");
    if (scanf("%ld %ld", &l, &r) != 2) {
        printf("Invalid input\n");
        return 1;
    }

    int64_t result = sum_of_odd_numbers(l, r);
    printf("Sum of odd numbers in range [%ld, %ld] = %ld\n", l, r, result);

    return 0;
}