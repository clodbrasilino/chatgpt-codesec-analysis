#include <stdio.h>
#include <limits.h>

long long count_squares(int length, int width) {
    if (length <= 0 || width <= 0) {
        return 0;
    }
    
    long long total = 0;
    int min = length < width ? length : width;
    int max = length > width ? length : width;
    
    for (int k = 0; k < min; k++) {
        long long term1 = (long long)(min - k);
        long long term2 = (long long)(max - k);
        
        if (term1 > LLONG_MAX / term2) {
            return -1;
        }
        
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9222160285916505066 + 12345512988212496 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000003,time:2208,execs:1431,op:havoc,rep:2)
         */
        total += term1 * term2;
        
        if (total < 0) {
            return -1;
        }
    }
    
    return total;
}

int main(void) {
    int length, width;
    
    printf("Enter length and width of rectangle: ");
    if (scanf("%d %d", &length, &width) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    long long result = count_squares(length, width);
    if (result == -1) {
        fprintf(stderr, "Overflow detected\n");
        return 1;
    }
    
    printf("Number of squares: %lld\n", result);
    
    return 0;
}