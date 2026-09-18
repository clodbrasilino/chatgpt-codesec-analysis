#include <stdio.h>
#include <stdint.h>

int64_t nth_hexagonal_number(int64_t n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 * -3 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000002,time:356,execs:165,op:havoc,rep:2)
     * UBSan: signed integer overflow: 2 * 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000002,time:356,execs:165,op:havoc,rep:2)
     * UBSan: signed integer overflow: 5555555555 * 11111111109 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000002,time:374,execs:172,op:havoc,rep:2)
     */
    int64_t result = n * (2 * n - 1);
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2 * 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000002,time:356,execs:165,op:havoc,rep:2)
     */
    if (n > 0 && (result / n) != (2 * n - 1)) {
        return -1;
    }
    return result;
}

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) == 1 && n > 0) {
        int64_t hex_num = nth_hexagonal_number(n);
        if (hex_num == -1) {
            printf("Integer overflow occurred. Please enter a smaller positive integer.\n");
        } else {
            printf("The %ldth hexagonal number is: %ld\n", n, hex_num);
        }
    } else {
        printf("Invalid input. Please enter a positive integer.\n");
    }
    return 0;
}