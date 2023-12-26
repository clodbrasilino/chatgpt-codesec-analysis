#include <stdio.h>
#include <limits.h>

int countUnsetBits(unsigned int n) {
    int count = 0;
    for (unsigned int num = 1; num <= n; num++) {
        for (unsigned int bit = 0; bit < sizeof(int) * CHAR_BIT; bit++) {
            unsigned int mask = 1u << bit;
            if ((num & mask) == 0) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    unsigned int n = 0;
    printf("Enter a number: ");
    scanf("%u", &n);
    printf("Total unset bits from 1 to %u: %d\n", n, countUnsetBits(n));
    return 0;
}
