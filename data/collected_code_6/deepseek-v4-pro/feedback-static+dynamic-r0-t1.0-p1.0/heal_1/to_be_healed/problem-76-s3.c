#include <stdio.h>
#include <stdlib.h>

long long count_squares_in_rectangle(int length, int width) {
    if (length <= 0 || width <= 0) {
        return -1;
    }
    
    long long total = 0;
    int min_dimension = length < width ? length : width;
    
    for (int size = 1; size <= min_dimension; size++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223353054664398814 + 44601382672128 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:9040,execs:5738,op:havoc,rep:10)
         */
        total += (long long)(length - size + 1) * (width - size + 1);
    }
    
    return total;
}

int main(void) {
    int length, width;
    
    printf("Enter rectangle dimensions (length width): ");
    if (scanf("%d %d", &length, &width) != 2) {
        fprintf(stderr, "Error: Invalid input format\n");
        return EXIT_FAILURE;
    }
    
    long long result = count_squares_in_rectangle(length, width);
    
    if (result == -1) {
        fprintf(stderr, "Error: Dimensions must be positive integers\n");
        return EXIT_FAILURE;
    }
    
    printf("Number of squares in %dx%d rectangle: %lld\n", length, width, result);
    
    return EXIT_SUCCESS;
}