#include <stdio.h>
#include <stdint.h>

int64_t centered_hexagonal_number(int64_t n) {
    int64_t result;
    if (n > 0 && n <= 9223372036854775807 / 3) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 6666666666666666666 * 2222222222222222221 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000002,time:405,execs:162,op:havoc,rep:1)
         */
        result = 3 * n * (n - 1) + 1;
    } else {
        result = -1;
    }
    return result;
}

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1) {
        return 1;
    }
    int64_t result = centered_hexagonal_number(n);
    if (result == -1) {
        printf("Invalid input. The number is too large.\n");
    } else {
        printf("The %ldth centered hexagonal number is: %ld\n", n, result);
    }
    return 0;
}