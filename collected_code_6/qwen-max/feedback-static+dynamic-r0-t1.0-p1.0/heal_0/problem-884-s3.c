#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

bool areBitsInRange(uint32_t num, int start, int end) {
    uint32_t mask = ((1U << (end - start + 1)) - 1) << start;
    return (num & mask) == (num >> start << start);
}

int main() {
    uint32_t num = 0b10101010101010101010101010101010;
    int start = 5;
    int end = 15;
    if (areBitsInRange(num, start, end)) {
        printf("All bits in the range %d to %d are within the given range.\n", start, end);
    } else {
        printf("Not all bits in the range %d to %d are within the given range.\n", start, end);
    }
    return 0;
}