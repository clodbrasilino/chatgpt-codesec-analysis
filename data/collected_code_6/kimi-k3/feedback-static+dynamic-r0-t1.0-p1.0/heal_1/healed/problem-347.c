#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long count_squares(int width, int height) {
    if (width <= 0 || height <= 0) {
        return -1;
    }
    
    long long w = (long long)width;
    long long h = (long long)height;
    long long total = 0;
    
    while (w > 0 && h > 0) {
        if (w > LLONG_MAX / h) {
            return -1;
        }
        long long term = w * h;
        if (total > LLONG_MAX - term) {
            return -1;
        }
        total += term;
        w--;
        h--;
    }
    
    return total;
}

int main(void) {
    int width = 0;
    int height = 0;
    
    printf("Enter rectangle width: ");
    if (scanf("%d", &width) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter rectangle height: ");
    if (scanf("%d", &height) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    long long result = count_squares(width, height);
    if (result < 0) {
        fprintf(stderr, "Invalid dimensions\n");
        return EXIT_FAILURE;
    }
    
    printf("Number of squares: %lld\n", result);
    
    return EXIT_SUCCESS;
}