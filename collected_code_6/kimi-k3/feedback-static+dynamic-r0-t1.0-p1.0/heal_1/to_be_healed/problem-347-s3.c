#include <stdio.h>
#include <stdlib.h>

long long count_squares(int width, int height) {
    if (width <= 0 || height <= 0) {
        return 0;
    }
    
    long long w = width;
    long long h = height;
    long long total = 0;
    long long min_dim = (w < h) ? w : h;
    
    for (long long size = 1; size <= min_dim; size++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 8288378658703455787 + 1381396434032326720 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000003,time:2558,execs:1117,op:havoc,rep:2)
         */
        total += (w - size + 1) * (h - size + 1);
    }
    
    return total;
}

int main(void) {
    int width, height;
    
    if (scanf("%d %d", &width, &height) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (width <= 0 || height <= 0) {
        fprintf(stderr, "Dimensions must be positive integers\n");
        return EXIT_FAILURE;
    }
    
    long long result = count_squares(width, height);
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}