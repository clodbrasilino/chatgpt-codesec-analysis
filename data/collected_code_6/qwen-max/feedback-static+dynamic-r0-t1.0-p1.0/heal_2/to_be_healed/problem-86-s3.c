#include <stdio.h>
#include <stdint.h>

int64_t nth_centered_hexagonal_number(int64_t n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 6666666666666666 * 2222222222222221 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000002,time:297,execs:133,op:havoc,rep:1)
     * UBSan: signed integer overflow: 3 * 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000002,time:320,execs:140,op:havoc,rep:4)
     * UBSan: signed integer overflow: 9223372036854775805 * 9223372036854775806 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000002,time:320,execs:140,op:havoc,rep:4)
     */
    return 3 * n * (n - 1) + 1;
}

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1 || n <= 0) {
        printf("Please enter a positive integer.\n");
        return 1;
    }
    int64_t result = nth_centered_hexagonal_number(n);
    printf("The %ldth centered hexagonal number is: %ld\n", n, result);
    return 0;
}