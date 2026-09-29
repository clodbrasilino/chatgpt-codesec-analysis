#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long countSetBitsHelper(int n) {
    if (n <= 0) {
        return 0;
    }
    
    int x = 0;
    while ((1 << x) <= n) {
        x++;
    }
    x--;
    
    /* Possible weaknesses found:
     * UBSan: shift exponent -1 is negative (AFL crash: id:000000,sig:06,src:000003,time:220,execs:125,op:quick,pos:1)
     */
    long long bits_till_2_to_x = (long long)x * (1 << (x - 1));
    long long msb_from_2_to_x_to_n = n - (1 << x) + 1;
    long long rest = countSetBitsHelper(n - (1 << x));
    
    return bits_till_2_to_x + msb_from_2_to_x_to_n + rest;
}

long long countSetBits(int n) {
    if (n < 0) {
        return -1;
    }
    return countSetBitsHelper(n);
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000003,time:242,execs:135,op:havoc,rep:1; likely memory-safety defect
  */

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        fprintf(stderr, "Input must be a non-negative integer\n");
        return EXIT_FAILURE;
    }
    
    long long totalBits = countSetBits(n);
    printf("%lld\n", totalBits);
    
    return EXIT_SUCCESS;
}