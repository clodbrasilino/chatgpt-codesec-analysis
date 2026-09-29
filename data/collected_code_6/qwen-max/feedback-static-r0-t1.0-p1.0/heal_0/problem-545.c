#include <stdio.h>
#include <stdint.h>

uint32_t toggleFirstLastBits(uint32_t num) {
    uint32_t mask = 1 | (1 << 31);
    return num ^ mask;
}

int main() {
    uint32_t num, result;
    printf("Enter a number: ");
    scanf("%u", &num);
    result = toggleFirstLastBits(num);
    printf("Result: %u\n", result);
    return 0;
}