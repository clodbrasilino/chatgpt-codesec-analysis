#include <stdio.h>

int countUnsetBits(int n) {
    int count = 0;
    for (int num = 1; num <= n; num++) {
        for (int bit = 0; bit < sizeof(int) * 8; bit++) {
            if ((num & (1 << bit)) == 0) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Total unset bits from 1 to %d: %d\n", n, countUnsetBits(n));
    return 0;
}