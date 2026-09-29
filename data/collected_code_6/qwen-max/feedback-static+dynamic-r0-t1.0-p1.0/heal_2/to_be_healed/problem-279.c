#include <stdio.h>
#include <stdint.h>

int64_t nth_decagonal_number(int64_t n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 3 * 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000001,time:794,execs:371,op:havoc,rep:1)
     * UBSan: signed integer overflow: -4 * 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000001,time:794,execs:371,op:havoc,rep:1)
     * UBSan: signed integer overflow: 88888888888888888 * 22222222222222222 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:691,execs:327,op:havoc,rep:7)
     * UBSan: signed integer overflow: 4 * 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000001,time:794,execs:371,op:havoc,rep:1)
     */
    int64_t result = 4 * n * n - 3 * n;
    return result;
}

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    if(scanf("%ld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    int64_t result = nth_decagonal_number(n);
    printf("The %ldth decagonal number is: %ld\n", n, result);
    return 0;
}