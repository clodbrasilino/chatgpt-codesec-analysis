#include <stdio.h>

int countSetBits(int n) {
    int bitCount = 0;
    for (int i = 1; i <= n; i++) {
        int j = i;
        while (j) {
            bitCount += j & 1;
            j = j >> 1;
        }
    }
    return bitCount;
}

int main() {
    int n;
    printf("Enter a number: ");
    if(scanf("%d", &n) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    if(n < 1) {
        printf("Number must be greater than 0.\n");
        return 2;
    }
    printf("Total set bits from 1 to %d  include: %d\n", n, countSetBits(n));
    return 0;
}