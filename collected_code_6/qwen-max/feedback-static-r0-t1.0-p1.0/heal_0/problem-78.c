#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

bool is_odd_set_bits(uint32_t num) {
    uint32_t count = 0;
    while (num > 0) {
        count += num & 1;
        num >>= 1;
    }
    return count % 2 == 1;
}

uint32_t count_int_with_odd_set_bits(uint32_t *array, size_t len) {
    uint32_t count = 0;
    for (size_t i = 0; i < len; i++) {
        if (is_odd_set_bits(array[i])) {
            count++;
        }
    }
    return count;
}

int main() {
    uint32_t numbers[] = {0b101, 0b110, 0b111, 0b100, 0b1001, 0b1010};
    size_t length = sizeof(numbers) / sizeof(numbers[0]);

    uint32_t result = count_int_with_odd_set_bits(numbers, length);

    printf("%u\n", result);

    return 0;
}