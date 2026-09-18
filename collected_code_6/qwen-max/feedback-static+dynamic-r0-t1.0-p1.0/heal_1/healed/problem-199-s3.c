#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int highestPowerOf2(int n) {
    if (n <= 0) return 0;
    uint32_t m = (uint32_t)n;
    m |= m >> 1;
    m |= m >> 2;
    m |= m >> 4;
    m |= m >> 8;
    m |= m >> 16;
    m = m + 1;
    return (m >> 1);
}

int main() {
    int number;
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        return 1;
    }
    int result = highestPowerOf2(number);
    printf("Highest power of two less than or equal to %d is %d\n", number, result);
    return 0;
}