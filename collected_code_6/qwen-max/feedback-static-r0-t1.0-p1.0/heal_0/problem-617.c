#include <stdio.h>
#include <math.h>

int calculateJumps(int d, int jumpLength) {
    if (jumpLength <= 0 || d < 0) {
        return -1; // Invalid input
    }
    if (d == 0) {
        return 0;
    }
    return (int) ceil((double)d / jumpLength);
}

int main() {
    int d = 15;
    int jumpLength = 4;

    int jumps = calculateJumps(d, jumpLength);

    if (jumps >= 0) {
        printf("Number of jumps required: %d\n", jumps);
    } else {
        printf("Invalid input.\n");
    }

    return 0;
}