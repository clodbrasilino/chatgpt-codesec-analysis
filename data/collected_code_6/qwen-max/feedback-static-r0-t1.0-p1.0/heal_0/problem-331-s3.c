#include <stdio.h>
#include <stdint.h>

int count_unset_bits(uint32_t num) {
    int count = 0;
    while (num) {
        if ((num & 1) == 0) {
            count++;
        }
        num >>= 1;
    }
    return count;
}

int main() {
    uint32_t number = 0b10101010101010101010101010101010;
    int result = count_unset_bits(number);
    printf("Number of unset bits: %d\n", result);
    return 0;
}