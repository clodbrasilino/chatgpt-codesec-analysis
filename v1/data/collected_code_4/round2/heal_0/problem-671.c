#include <stdio.h>

int modifyBit(int n, int p) {
    int mask = 1 << p;
    return (n | mask);
}

int rightMostUnsetBit(int n) {
    for (int i = 0; i < sizeof(int) * 8; i++) {
        if ((n & (1 << i)) == 0) {
            return modifyBit(n, i);
        }
    }
    return -1; // Unable to find unset bit
}

int main() {
    int n;
    printf("Enter a number:\n");
    scanf("%d", &n);
    int result = rightMostUnsetBit(n);
    if (result == -1) {
        printf("All bits are set\n");
    } else {
        printf("Number after setting the rightmost unset bit: %d\n", result);
    }
    return 0;
}