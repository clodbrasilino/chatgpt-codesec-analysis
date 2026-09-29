#include <stdio.h>

int has_even_parity(unsigned int num) {
    int count = 0;
    while (num) {
        count ^= (num & 1);
        num >>= 1;
    }
    return !count;
}

int main(void) {
    unsigned int test_values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 15, 16, 255, 256};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        printf("%u: %s\n", test_values[i], 
               has_even_parity(test_values[i]) ? "even parity" : "odd parity");
    }
    
    return 0;
}