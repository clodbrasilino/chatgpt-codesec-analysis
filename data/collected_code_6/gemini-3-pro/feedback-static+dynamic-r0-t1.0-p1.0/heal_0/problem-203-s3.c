#include <stdio.h>
#include <stdlib.h>

int hamming_distance(int x, int y) {
    int xor_val = x ^ y;
    int distance = 0;
    
    while (xor_val > 0) {
        distance += xor_val & 1;
        xor_val >>= 1;
    }
    
    return distance;
}

int main(void) {
    int num1 = 0;
    int num2 = 0;
    
    if (printf("Enter two integers: ") < 0) {
        return EXIT_FAILURE;
    }
    
    if (scanf("%d %d", &num1, &num2) != 2) {
        if (printf("Invalid input.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }
    
    if (num1 < 0 || num2 < 0) {
        if (printf("Please enter non-negative integers.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }
    
    int distance = hamming_distance(num1, num2);
    
    if (printf("Hamming distance: %d\n", distance) < 0) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}