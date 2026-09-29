#include <stdio.h>

int countSetBits(int n) {
    int count = 0;
    for (int i = 1; i <= n; i++) {
        int num = i;
        while (num) {
            count += num & 1;
            num >>= 1;
        }
    }
    return count;
}

int main() {
    int n;
    printf("Enter a number: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    int result = countSetBits(n);
    printf("Total set bits from 1 to %d is: %d\n", n, result);
    return 0;
}