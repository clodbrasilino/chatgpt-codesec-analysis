#include <stdio.h>
#include <assert.h>

unsigned int setRightmostUnsetBit(unsigned int n) {
    return n | (n + 1);
}

unsigned int setRightmostUnsetBitFixed(unsigned int n) {
    if (n == ~0u) return n;
    return n | (~n & -(~n));
}

int main(void) {
    unsigned int test_values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 15, 16};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        unsigned int input = test_values[i];
        unsigned int original = setRightmostUnsetBit(input);
        unsigned int fixed = setRightmostUnsetBitFixed(input);
        printf("Input: %u, Original: %u, Fixed: %u\n", input, original, fixed);
    }
    
    assert(setRightmostUnsetBitFixed(5) == 7);
    assert(setRightmostUnsetBitFixed(15) == 31);
    assert(setRightmostUnsetBitFixed(~0u) == ~0u);
    
    return 0;
}