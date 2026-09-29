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
    
    for (int i = 1; i < bit_count - 1; i++) {
        mask |= (1u << i);
    }
    
    return num ^ mask;
}

int main(void) {
    unsigned int test_values[] = {0, 1, 2, 3, 7, 8, 15, 16, 31, 255, 1024};
    int num_tests = sizeof(test_values) / sizeof(test_values[0]);
    
    for (int i = 0; i < num_tests; i++) {
        unsigned int input = test_values[i];
        unsigned int result = toggle_middle_bits(input);
        printf("Input: %u, Output: %u\n", input, result);
    }
    
    return 0;
}