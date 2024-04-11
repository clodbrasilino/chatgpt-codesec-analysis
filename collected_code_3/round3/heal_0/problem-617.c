#include <stdio.h>

int jumpsRequired(int d, int jumpLength) {
    if (jumpLength == 0) {
        return -1;
    }
    if (d % jumpLength == 0) {
        return d / jumpLength;
    } else {
        return d / jumpLength + 1;
    }
}

int main() {
    int d, jumpLength;
    printf("Enter the distance: ");
    scanf("%d", &d);
    printf("Enter the jump length: ");
    scanf("%d", &jumpLength);
    int result = jumpsRequired(d, jumpLength);
    if (result == -1) {
        printf("Jump length cannot be zero.\n");
    } else {
        printf("Number of jumps required: %d\n", result);
    }
    return 0;
}