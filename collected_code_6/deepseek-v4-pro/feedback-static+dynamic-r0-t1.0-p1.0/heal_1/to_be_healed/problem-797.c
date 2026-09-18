#include <stdio.h>
#include <stdlib.h>

long long sum_odd_range(int l, int r) {
    if (l > r) {
        return 0;
    }
    
    if (l % 2 == 0) {
        l++;
    }
    
    if (r % 2 == 0) {
        r--;
    }
    
    if (l > r) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 747385741 - -2072745073 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000005,time:3915,execs:2521,op:havoc,rep:6)
     */
    long long n = (r - l) / 2 + 1;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1724130191 + 1848304525 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000005,time:13547,execs:8727,op:havoc,rep:1)
     */
    return n * (l + r) / 2;
}

int main(void) {
    int l, r;
    
    printf("Enter range (l r): ");
    if (scanf("%d %d", &l, &r) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    long long result = sum_odd_range(l, r);
    printf("Sum of odd numbers in range [%d, %d]: %lld\n", l, r, result);
    
    return EXIT_SUCCESS;
}