#include <stdio.h>

int calculateJumps(int d) {
    // If the point is already at the origin, no jumps are required
    if (d == 0) {
        return 0;
    }
    // If the point is on the positive x-axis, a single jump is required
    else if (d > 0 && d <= 3) {
        return 1;
    }
    // Otherwise, calculate the number of jumps required based on the given formula
    else {
        int jumps = (d / 3) + (d % 3 != 0);
        return jumps;
    }
}

int main() {
    int d;
    printf("Enter the value of d: ");
    scanf("%d", &d);
    int jumps = calculateJumps(d);
    printf("Number of jumps required: %d\n", jumps);
    return 0;
}