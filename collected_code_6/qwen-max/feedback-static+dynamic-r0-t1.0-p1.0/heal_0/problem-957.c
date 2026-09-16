#include <stdio.h>
#include <limits.h>

int getRightmostSetBitPosition(unsigned int n) {
    int position = 0;
    while (n > 0) {
        if (n & 1) {
            return position;
        }
        position++;
        n >>= 1;
    }
    return -1; // No set bit found
}

int main() {
    unsigned int n = 18; // Example number
    int position = getRightmostSetBitPosition(n);
    if (position != -1) {
        printf("The position of the rightmost set bit is: %d\n", position);
    } else {
        printf("No set bits found.\n");
    }
    return 0;
}