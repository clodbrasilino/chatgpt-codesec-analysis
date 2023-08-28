#include <stdio.h>

int countSetBits(int n) {
    int count = 0;
    for (int i = 1; i <= n; i++) {
        int num = i;
        while (num > 0) {
            if (num & 1)
                count++;
            num >>= 1;
        }
    }
    return count;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    int result = countSetBits(n);
    printf("Total set bits from 1 to %d: %d\n", n, result);
    return 0;
}