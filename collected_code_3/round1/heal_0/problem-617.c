#include <stdio.h>

int numberOfJumps(int d, int length) {
    if (d % length == 0) {
        return d / length;
    } else {
        return d / length + 1;
    }
}

int main() {
    int d, length;
    printf("Enter the distance: ");
    scanf("%d", &d);
    printf("Enter the length of each jump: ");
    scanf("%d", &length);
    printf("Number of jumps required: %d\n", numberOfJumps(d, length));
    return 0;
}