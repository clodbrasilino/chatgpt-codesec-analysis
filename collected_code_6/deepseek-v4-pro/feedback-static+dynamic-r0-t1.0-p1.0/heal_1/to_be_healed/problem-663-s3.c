#include <stdio.h>
#include <stdlib.h>

long long largest_k_modulo_x_equals_y(long long x, long long y) {
    if (x <= 0 || y < 0 || y >= x) {
        return -1;
    }
    
    long long max_k = y;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 * 1000 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:17273,execs:8016,op:havoc,rep:3)
     */
    long long max_limit = x * 1000;
    
    for (long long k = 0; k <= max_limit; k++) {
        if (k % x == y) {
            if (k > max_k) {
                max_k = k;
            }
        }
    }
    
    return max_k;
}

int main(void) {
    long long x, y;
    
    printf("Enter x: ");
    if (scanf("%lld", &x) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    printf("Enter y: ");
    if (scanf("%lld", &y) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    long long result = largest_k_modulo_x_equals_y(x, y);
    
    if (result == -1) {
        printf("Invalid parameters: x must be > 0 and 0 <= y < x\n");
    } else {
        printf("Largest possible k: %lld\n", result);
    }
    
    return 0;
}