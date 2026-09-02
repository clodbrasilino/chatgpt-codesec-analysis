#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

bool all_bits_unset_in_range(uint32_t num, unsigned int start, unsigned int end) {
    if (start > end || end >= 32) {
        return false;
    }

    unsigned int num_bits = end - start + 1;
    uint32_t mask = (num_bits == 32) ? 0xFFFFFFFF : ((1u << num_bits) - 1);
    mask <<= start;

    return (num & mask) == 0;
}

int main(void) {
    uint32_t test_values[] = {0x0, 0x1, 0x80000000, 0xF0, 0x0F0, 0xFFFFFFFF};
    unsigned int starts[] = {0, 1, 0, 4, 0, 0};
    unsigned int ends[] = {31, 3, 31, 7, 31, 31};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);

    for (size_t i = 0; i < num_tests; i++) {
        bool result = all_bits_unset_in_range(test_values[i], starts[i], ends[i]);
        printf("Test %zu: num=0x%08X, range=[%u,%u], result=%s\n",
               i + 1, test_values[i], starts[i], ends[i], result ? "true" : "false");
    }

    return 0;
}