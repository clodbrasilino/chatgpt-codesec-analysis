#include <stdio.h>
#include <stdint.h>

int64_t nth_nonagonal(int64_t n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 7 * 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000001,time:261,execs:258,op:havoc,rep:4)
     * UBSan: signed integer overflow: 9223372036854775807 * 9223372036854775796 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000001,time:261,execs:258,op:havoc,rep:4)
     * UBSan: signed integer overflow: 1119111111111111111 * 7833777777777777772 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:156,execs:165,op:havoc,rep:11)
     */
    int64_t result = n * (7 * n - 5) / 2;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 7 * 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000001,time:261,execs:258,op:havoc,rep:4)
     */
    if (result / n != (7 * n - 5) / 2) {
        fprintf(stderr, "Integer overflow detected.\n");
        return -1;
    }
    return result;
}

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    if (n <= 0) {
        fprintf(stderr, "n must be a positive integer.\n");
        return 1;
    }
    int64_t nonagonal_number = nth_nonagonal(n);
    if (nonagonal_number == -1) {
        return 1;
    }
    printf("The %ldth nonagonal number is: %ld\n", n, nonagonal_number);
    return 0;
}