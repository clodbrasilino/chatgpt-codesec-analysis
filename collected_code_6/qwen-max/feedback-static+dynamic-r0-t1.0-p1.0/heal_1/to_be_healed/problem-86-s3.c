#include <stdio.h>

long nth_centered_hexagonal_number(long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 422109716990412 * 140703238996803 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000002,time:8,execs:15,op:(null),pos:0)
     * UBSan: signed integer overflow: 3 * 9223372036854775807 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000002,time:328,execs:111,op:havoc,rep:1)
     * UBSan: signed integer overflow: 9223372036854775805 * 9223372036854775806 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000002,time:328,execs:111,op:havoc,rep:1)
     */
    return 3 * n * (n - 1) + 1;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    scanf("%ld", &n);
    if (n <= 0) {
        printf("Please enter a positive integer.\n");
        return 1;
    }
    long result = nth_centered_hexagonal_number(n);
    printf("The %ldth centered hexagonal number is: %ld\n", n, result);
    return 0;
}