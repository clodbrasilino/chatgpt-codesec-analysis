#include <stdio.h>

int count_squares(int length, int width) {
    int min = (length < width) ? length : width;
    int max = (length > width) ? length : width;
    int total = 0;
    int i;
    
    for (i = 0; i < min; i++) {
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