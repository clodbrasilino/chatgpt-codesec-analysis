#include <stdio.h>

int calculateJumps(int d, int length) {
    int jumps = d / length;
    if (d % length != 0) {
        jumps++;
    }
    return jumps;
}

int main() {
    int d, length;
    printf("Enter the distance from origin: ");
    scanf("%d", &d);
    printf("Enter the length of each jump: ");
    scanf("%d", &length);
    int jumps = calculateJumps(d, length);
    printf("Number of jumps required: %d\n", jumps);
    return 0;
}