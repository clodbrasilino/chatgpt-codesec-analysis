#include <stdio.h>

unsigned int count_set_bits(unsigned int num) {
    unsigned int count = 0;
    while (num != 0) {
        count += num & 1U;
        num >>= 1;
    }
    return count;
}

int main(void) {
    unsigned int test_values[] = {0, 1, 2, 3, 255, 256, 4294967295U};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    size_t i;

    for (i = 0; i < num_tests; ++i) {
        printf("Number: %u, Set bits: %u\n", test_values[i], count_set_bits(test_values[i]));
    }

    return 0;
}