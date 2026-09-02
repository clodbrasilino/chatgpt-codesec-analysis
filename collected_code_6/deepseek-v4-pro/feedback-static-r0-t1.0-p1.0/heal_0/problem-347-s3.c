#include <stdio.h>
#include <stdlib.h>

long long count_squares(int length, int width) {
    if (length <= 0 || width <= 0) {
        return 0;
    }
    
    long long total = 0;
    int min_dim = length < width ? length : width;
    
    for (int size = 1; size <= min_dim; size++) {
        total += (long long)(length - size + 1) * (width - size + 1);
    }
    
    return total;
}

int main(void) {
    int length, width;
    
    printf("Enter length and width of rectangle: ");
    if (scanf("%d %d", &length, &width) != 2) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    long long result = count_squares(length, width);
    printf("Number of squares: %lld\n", result);
    
    return EXIT_SUCCESS;
}