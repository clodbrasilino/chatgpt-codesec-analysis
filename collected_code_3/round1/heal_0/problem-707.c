#include <stdio.h>

int countSetBits(int n) {
    int bitCount = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < 32; j++)
            if ((i >> j) & 1)
                bitCount++;
    return bitCount;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Total set bits from 1 to %d is %d\n", n, countSetBits(n));
    return 0;
}