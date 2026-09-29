#include <stdio.h>

long nth_star_number(long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 6 * 9223372036854775807 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:577,execs:222,op:havoc,rep:5)
     * UBSan: signed integer overflow: -6 * 9223372036854775806 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:577,execs:222,op:havoc,rep:5)
     * UBSan: signed integer overflow: 199940002400004 * 33323333733333 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:327,execs:134,op:havoc,rep:12)
     */
    return 6 * n * (n - 1) + 1;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if(scanf("%ld", &n) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    printf("The %ldth star number is: %ld\n", n, nth_star_number(n));
    return 0;
}