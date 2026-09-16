#include <stdio.h>
#include <stdint.h>

int has_even_parity(uint32_t num) {
    uint32_t count = 0;
    while (num) {
        count += num & 1;
        num >>= 1;
    }
    return (count % 2 == 0);
}

int main(void) {
    uint32_t test_values[] = {0, 1, 2, 3, 4, 5, 0xFFFFFFFF};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        printf("Number: %u, Even parity: %s\n", 
               test_values[i], 
               has_even_parity(test_values[i]) ? "Yes" : "No");
    }
    
    return 0;
}