#include <stdio.h>
#include <math.h>

int calculateJumps(int d, int jumpLength) {
    return (int)ceil((double)d / jumpLength);
}

int main() {
    int d, jumpLength;
    printf("Enter the destination (d, 0): ");
    scanf("%d", &d);
    printf("Enter the jump length: ");
    scanf("%d", &jumpLength);

    if (d <= 0 || jumpLength <= 0) {
        printf("Invalid input. Distance and jump length must be positive.\n");
        return 1;
    }

    int numberOfJumps = calculateJumps(d, jumpLength);
    printf("Number of jumps required: %d\n", numberOfJumps);

    return 0;
}