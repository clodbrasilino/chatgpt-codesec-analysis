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