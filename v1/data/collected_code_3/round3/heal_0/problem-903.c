#include <stdio.h>

int countUnsetBits(unsigned int n) {
    unsigned int totalBits = sizeof(n) * 8;
    unsigned int setBits = 0;
    while (n) {
        n &= (n - 1);
        setBits++;
    }
    return totalBits - setBits;
}

int totalUnsetBitsFrom1ToN(int n) {
    int totalUnsetBits = 0;
    for (int i = 1; i <= n; i++) {
        totalUnsetBits += countUnsetBits(i);
    }
    return totalUnsetBits;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Total unset bits from 1 to %d is %d\n", n, totalUnsetBitsFrom1ToN(n));
    return 0;
}