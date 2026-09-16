#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

bool check_even_parity(uint32_t num) {
    uint32_t count = 0;
    uint32_t temp = num;
    
    while (temp != 0U) {
        count ^= (temp & 1U);
        temp >>= 1U;
    }
    
    return (count == 0U);
}

int main(void) {
    uint32_t test_values[] = {0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 255U};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    
    for (size_t i = 0U; i < num_tests; i++) {
        if (check_even_parity(test_values[i])) {
            printf("%u has even parity\n", test_values[i]);
        } else {
            printf("%u has odd parity\n", test_values[i]);
        }
    }
    
    return 0;
}