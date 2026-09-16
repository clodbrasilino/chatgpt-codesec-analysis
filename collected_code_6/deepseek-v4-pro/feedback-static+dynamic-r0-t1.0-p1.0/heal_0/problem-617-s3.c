#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int min_jumps(int d, int jump_length) {
    if (jump_length <= 0) {
        return -1;
    }
    
    if (d == 0) {
        return 0;
    }
    
    int abs_d = abs(d);
    
    if (abs_d < jump_length) {
        return 2;
    }
    
    return (abs_d + jump_length - 1) / jump_length;
}

int main(void) {
    int d, jump_length;
    
    printf("Enter the target x-coordinate (d): ");
    if (scanf("%d", &d) != 1) {
        fprintf(stderr, "Invalid input for d\n");
        return 1;
    }
    
    printf("Enter the jump length: ");
    if (scanf("%d", &jump_length) != 1) {
        fprintf(stderr, "Invalid input for jump length\n");
        return 1;
    }
    
    int result = min_jumps(d, jump_length);
    
    if (result == -1) {
        printf("Invalid jump length. Jump length must be positive.\n");
    } else {
        printf("Minimum jumps required: %d\n", result);
    }
    
    return 0;
}