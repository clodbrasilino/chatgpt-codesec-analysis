#include <stdio.h>

long long decagonal_number(long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 3 * 9223372036854775807 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:6681,execs:2761,op:havoc,rep:2)
     * UBSan: signed integer overflow: -4 * 9223372036854775807 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:6681,execs:2761,op:havoc,rep:2)
     * UBSan: signed integer overflow: 39719999996 * 9929999999 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000000,time:2310,execs:891,op:havoc,rep:8)
     * UBSan: signed integer overflow: 4 * 9223372036854775807 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:6681,execs:2761,op:havoc,rep:2)
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
    long long result = decagonal_number(n);
    printf("The %ldth decagonal number is: %lld\n", n, result);
    return 0;
}