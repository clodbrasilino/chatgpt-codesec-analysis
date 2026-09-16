#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool has_odd_parity(unsigned int number);

bool has_odd_parity(unsigned int number) {
    bool parity = false;
    while (number > 0) {
        parity = !parity;
        number = number & (number - 1U);
    }
    return parity;
}

int main(void) {
    unsigned int test_values[] = {0, 1, 2, 3, 4, 5, 255, 256};
    size_t num_values = sizeof(test_values) / sizeof(test_values[0]);

    for (size_t i = 0; i < num_values; ++i) {
        unsigned int val = test_values[i];
        bool parity_is_odd = has_odd_parity(val);
        printf("%u: %d\n", val, parity_is_odd);
    }

    return EXIT_SUCCESS;
}