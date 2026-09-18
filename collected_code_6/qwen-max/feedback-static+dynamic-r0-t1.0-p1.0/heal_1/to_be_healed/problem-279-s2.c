#include <stdio.h>

long decagonal_number(long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 4 * 9223372036854775807 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:616,execs:300,op:havoc,rep:2)
     * UBSan: signed integer overflow: 3 * 9223372036854775807 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:616,execs:300,op:havoc,rep:2)
     * UBSan: signed integer overflow: -4 * 9223372036854775807 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:616,execs:300,op:havoc,rep:2)
     * UBSan: signed integer overflow: 149333333332 * 37333333333 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:3405,execs:1393,op:havoc,rep:9)
     */
    return 4 * n * n - 3 * n;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    long result = decagonal_number(n);
    printf("The %ldth decagonal number is: %ld\n", n, result);
    return 0;
}