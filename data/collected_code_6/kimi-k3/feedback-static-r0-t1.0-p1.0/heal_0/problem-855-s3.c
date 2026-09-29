#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool has_even_parity(unsigned int num) {
    bool parity = false;
    while (num != 0U) {
        parity = !parity;
        num &= (num - 1U);
    }
    return parity;
}

int main(void) {
    unsigned int test_values[] = {0U, 1U, 3U, 5U, 7U, 15U, 255U, 256U};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    
    for (size_t i = 0U; i < num_tests; i++) {
        printf("Number: %u, Even Parity: %s\n", 
               test_values[i], 
               has_even_parity(test_values[i]) ? "true" : "false");
    }
    
    return 0;
}