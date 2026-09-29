#include <stdio.h>
#include <stdint.h>

uint32_t set_right_most_unset_bit(uint32_t n) {
    return (n | (n + 1)) & -((int32_t)(n + 1));
}

uint32_t corrected_set_right_most_unset_bit(uint32_t n) {
    return (n | (n + 1)) & (~n);
}

int main() {
    uint32_t test_cases[] = {0b10111, 0b1111, 0b1011};
    const uint32_t expected_results[] = {0b11011, 0b1111, 0b1111};
    int num_test_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_test_cases; ++i) {
        uint32_t result = corrected_set_right_most_unset_bit(test_cases[i]);
        printf("Test case %d: Expected %u, got %u\n", i, expected_results[i], result);
    }

    uint32_t n = 0b101010;
    n = corrected_set_right_most_unset_bit(n);
    printf("%u\n", n);

    return 0;
}