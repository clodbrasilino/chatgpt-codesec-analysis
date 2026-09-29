#include <stdio.h>

long nth_decagonal_number(long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -5113410740376218284 * 3333333333333333333 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:494,execs:202,op:havoc,rep:4)
     * UBSan: signed integer overflow: 13333333332 * 3333333333 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:368,execs:152,op:havoc,rep:7)
     * UBSan: signed integer overflow: 4 * 3333333333333333333 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:494,execs:202,op:havoc,rep:4)
     * UBSan: signed integer overflow: 3 * 3333333333333333333 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:494,execs:202,op:havoc,rep:4)
     */
    return 4 * n * n - 3 * n;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if(scanf("%ld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    long result = nth_decagonal_number(n);
    printf("The %ldth decagonal number is: %ld\n", n, result);
    return 0;
}