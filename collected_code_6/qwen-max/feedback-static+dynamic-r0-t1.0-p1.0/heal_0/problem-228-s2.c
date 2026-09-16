#include <stdio.h>
#include <stdbool.h>

bool areBitsUnsetInRange(unsigned int num, int start, int end) {
    unsigned int mask = ((1U << (end - start + 1)) - 1) << start;
    return (num & mask) == 0;
}

int main() {
    unsigned int num = 0b1010101010101010; // Example number
    int start = 2;
    int end = 5;

    if (areBitsUnsetInRange(num, start, end)) {
        printf("All bits in the range %d to %d are unset.\n", start, end);
    } else {
        printf("Not all bits in the range %d to %d are unset.\n", start, end);
    }

    return 0;
}