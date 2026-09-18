#include <stdio.h>

long long count_squares(int length, int width) {
    if (length <= 0 || width <= 0) {
        return 0;
    }
    
    long long total = 0;
    int min = length < width ? length : width;
    int max = length > width ? length : width;
    
    for (int k = 0; k < min; k++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223321299783633847 + 51985856481995 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000003,time:3831,execs:2502,op:havoc,rep:8)
         */
        total += (long long)(min - k) * (max - k);
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
    
    printf("Number of squares: %lld\n", count_squares(length, width));
    
    return 0;
}