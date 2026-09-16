#include <stdio.h>
#include <stdbool.h>

bool all_bits_unset_in_range(unsigned int num, unsigned int start, unsigned int end) {
    if (start > end || end >= sizeof(unsigned int) * 8) {
        return false;
    }
    
    unsigned int range_length = end - start + 1;
    unsigned int mask;
    
    if (range_length == sizeof(unsigned int) * 8) {
        mask = ~0u;
    } else {
        mask = ((1u << range_length) - 1) << start;
    }
    
    return (num & mask) == 0;
}

int main(void) {
    unsigned int test_cases[][3] = {
        {0x00000000, 0, 31},
        {0xFFFFFFFF, 0, 31},
        {0x0000000F, 0, 3},
        {0x000000F0, 4, 7},
        {0x12345678, 8, 15},
        {0x80000000, 31, 31},
        {0x00000001, 0, 0}
    };
    
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (int i = 0; i < num_tests; i++) {
        printf("Number: 0x%08X, Range: %u-%u, Result: %s\n",
               test_cases[i][0],
               test_cases[i][1],
               test_cases[i][2],
               all_bits_unset_in_range(test_cases[i][0], test_cases[i][1], test_cases[i][2]) ? "true" : "false");
    }
    
    return 0;
}