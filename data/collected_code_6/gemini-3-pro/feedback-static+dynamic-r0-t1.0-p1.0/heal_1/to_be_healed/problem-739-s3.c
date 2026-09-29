#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long find_smallest_triangular_index(int n) {
    if (n <= 0) {
        return -1;
    }
    
    double target = pow(10.0, n - 1);
    /* Possible weaknesses found:
     * UBSan: inf is outside the range of representable values of type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:295,execs:151,op:havoc,rep:1)
     */
    long long index = (long long)ceil((-1.0 + sqrt(1.0 + 8.0 * target)) / 2.0);
    
    return index;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }
    
    long long index = find_smallest_triangular_index(n);
    if (index == -1) {
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", index);
    
    return EXIT_SUCCESS;
}