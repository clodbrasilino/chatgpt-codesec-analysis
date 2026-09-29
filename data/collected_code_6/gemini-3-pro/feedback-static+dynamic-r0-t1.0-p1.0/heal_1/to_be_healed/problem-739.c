#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long find_smallest_triangular_index(int n) {
    if (n <= 0) {
        return -1;
    }
    
    /* Possible weaknesses found:
     * UBSan: 1e+32 is outside the range of representable values of type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:488,execs:241,op:havoc,rep:3)
     */
    long long target = (long long)pow(10, n - 1);
    /* Possible weaknesses found:
     * UBSan: nan is outside the range of representable values of type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:488,execs:241,op:havoc,rep:3)
     */
    long long k = (long long)ceil((-1.0 + sqrt(1.0 + 8.0 * target)) / 2.0);
    
    return k;
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