#include <stdio.h>

int min_jumps(int d, int length) {
    if (length <= 0 || d < 0) {
        return -1;
    }
    
    if (d == 0) {
        return 0;
    }
    
    if (length >= d) {
        if (d == length) {
            return 1;
        } else {
            if (length - d == 1) {
                return 1;
            }
            return 2;
        }
    }
    
    int jumps = d / length;
    int remaining = d % length;
    
    if (remaining == 0) {
        return jumps;
    }
    
    if (jumps >= 1) {
        int extra = length - remaining;
        if (extra <= jumps - 1) {
            return jumps + 2;
        }
    }
    
    return jumps + 1;
}

int main(void) {
    int d, length, result;
    
    d = 10;
    length = 3;
    result = min_jumps(d, length);
    if (result == -1) {
        printf("Invalid input\n");
    } else {
        printf("Minimum jumps required: %d\n", result);
    }
    
    d = 5;
    length = 2;
    result = min_jumps(d, length);
    if (result == -1) {
        printf("Invalid input\n");
    } else {
        printf("Minimum jumps required: %d\n", result);
    }
    
    d = 0;
    length = 5;
    result = min_jumps(d, length);
    printf("Minimum jumps required: %d\n", result);
    
    d = 7;
    length = 5;
    result = min_jumps(d, length);
    if (result == -1) {
        printf("Invalid input\n");
    } else {
        printf("Minimum jumps required: %d\n", result);
    }
    
    return 0;
}