#include <stdio.h>

int countSetBits(int n) {
    int count = 0;
    for (int i = 1; i <= n; i++) {
        int x = i;
        while (x != 0) {
            count += x & 1;
            x >>= 1;
        }
    }
    return count;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    int result = countSetBits(n);
    printf("Total set bits from 1 to %d is %d\n", n, result);
    return 0;
}