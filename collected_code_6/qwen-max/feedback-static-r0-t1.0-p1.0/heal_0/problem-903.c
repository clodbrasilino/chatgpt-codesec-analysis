#include <stdio.h>
#include <stdint.h>

int count_unset_bits(int n) {
    int unsetBits = 0;
    for (int i = 1; i <= n; ++i) {
        uint32_t value = i;
        while (value) {
            if ((value & 1) == 0)
                unsetBits++;
            value >>= 1;
        }
    }
    return unsetBits;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    int result = count_unset_bits(n);
    printf("Total unset bits from 1 to %d is %d\n", n, result);
    return 0;
}