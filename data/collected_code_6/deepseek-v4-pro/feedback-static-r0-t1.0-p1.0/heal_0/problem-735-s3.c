#include <stdio.h>

unsigned int toggle_middle_bits(unsigned int num) {
    if (num == 0 || num == 1) {
        return num;
    }

    unsigned int mask = 0;
    unsigned int temp = num;
    int bit_count = 0;

    while (temp > 0) {
        temp >>= 1;
        bit_count++;
    }

    if (bit_count <= 2) {
        return num;
    }

    for (int i = 1; i < bit_count - 1; i++) {
        mask |= (1u << i);
    }

    return num ^ mask;
}

int main(void) {
    unsigned int test_cases[] = {0, 1, 2, 3, 4, 5, 7, 8, 10, 15, 16, 31, 32, 255, 256};
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_tests; i++) {
        printf("toggle_middle_bits(%u) = %u\n", test_cases[i], toggle_middle_bits(test_cases[i]));
    }

    return 0;
}