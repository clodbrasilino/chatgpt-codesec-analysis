#include <stdio.h>

long long difference_of_squares(int n) {
    if (n < 0) {
        return -1;
    }
    
    long long sum = (long long)n * (n + 1) / 2;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 12345679320987656 * 222222225 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:271,execs:127,op:havoc,rep:1)
     * UBSan: signed integer overflow: 2 * 1891135943 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:621,execs:270,op:havoc,rep:4)
     * UBSan: signed integer overflow: 3576395156797635192 * -512695409 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:621,execs:270,op:havoc,rep:4)
     */
    long long sum_sq = (long long)n * (n + 1) * (2 * n + 1) / 6;
    
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1788197578398817596 * 1788197578398817596 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:621,execs:270,op:havoc,rep:4)
     * UBSan: signed integer overflow: 6172839660493828 * 6172839660493828 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:271,execs:127,op:havoc,rep:1)
     * UBSan: signed integer overflow: 617284382716 * 617284382716 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:741,execs:319,op:havoc,rep:4)
     */
    return sum * sum - sum_sq;
}

int main(void) {
    int n;
    
    printf("Enter a natural number: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (n < 0) {
        fprintf(stderr, "Number must be non-negative\n");
        return 1;
    }
    
    printf("Difference: %lld\n", difference_of_squares(n));
    
    return 0;
}