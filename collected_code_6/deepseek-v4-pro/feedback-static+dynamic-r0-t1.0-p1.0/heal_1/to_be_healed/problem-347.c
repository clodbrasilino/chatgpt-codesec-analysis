#include <stdio.h>

int count_squares(int length, int width) {
    int min = (length < width) ? length : width;
    int max = (length > width) ? length : width;
    int total = 0;
    int i;
    
    for (i = 0; i < min; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2139992085 + 97776976 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000003,time:3950,execs:1547,op:havoc,rep:3)
         * UBSan: signed integer overflow: 747385742 * 3 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000003,time:1324,execs:487,op:havoc,rep:12)
         */
        total += (max - i) * (min - i);
    }
    
    return total;
}

int main(void) {
    int length, width;
    
    printf("Enter length: ");
    if (scanf("%d", &length) != 1) {
        return 1;
    }
    
    printf("Enter width: ");
    if (scanf("%d", &width) != 1) {
        return 1;
    }
    
    if (length <= 0 || width <= 0) {
        printf("Dimensions must be positive integers.\n");
        return 1;
    }
    
    printf("Number of squares: %d\n", count_squares(length, width));
    
    return 0;
}