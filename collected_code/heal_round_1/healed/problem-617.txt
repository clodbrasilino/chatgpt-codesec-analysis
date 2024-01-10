#include <stdio.h>

int calculateJumps(int d) {
    if (d == 0) {
        return 0;
    }
    else if (d > 0 && d <= 3) {
        return 1;
    }
    else {
        int jumps = (d / 3) + (d % 3 != 0);
        return jumps;
    }
}

int main() {
    int d = 0;
    printf("Enter the value of d: ");
    scanf("%d", &d);
    int jumps = calculateJumps(d);
    printf("Number of jumps required: %d\n", jumps);
    return 0;
}