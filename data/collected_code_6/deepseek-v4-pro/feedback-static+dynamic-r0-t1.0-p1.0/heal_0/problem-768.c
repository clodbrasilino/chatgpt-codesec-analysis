#include <stdio.h>
#include <stdint.h>

int check_odd_parity(uint32_t num) {
    uint32_t parity = num;
    parity ^= parity >> 16;
    parity ^= parity >> 8;
    parity ^= parity >> 4;
    parity ^= parity >> 2;
    parity ^= parity >> 1;
    return (int)(parity & 1U);
}

int main(void) {
    uint32_t numbers[] = {0U, 1U, 2U, 3U, 7U, 8U, 15U, 16U, 255U, 256U};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        printf("%u: %d\n", numbers[i], check_odd_parity(numbers[i]));
    }

    return 0;
}