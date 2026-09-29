#include <stdio.h>
#include <stdlib.h>

int get_rightmost_set_bit_position(unsigned int n);

int get_rightmost_set_bit_position(unsigned int n) {
    int position = 1;

    if (n == 0) {
        return 0;
    }

    while ((n & 1U) == 0) {
        n >>= 1;
        position++;
    }

    return position;
}

int main(void) {
    unsigned int test_values[] = {0, 1, 2, 12, 18, 20};
    size_t num_values = sizeof(test_values) / sizeof(test_values[0]);
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'position' can be reduced. [variableScope]
     */
    int position;

    for (i = 0; i < num_values; i++) {
        position = get_rightmost_set_bit_position(test_values[i]);
        /* Possible weaknesses found:
         *  %u in format string (no. 1) requires 'unsigned int' but the argument type is 'signed int'. [invalidPrintfArgType_uint]
         */
        if (printf("%u\n", position) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}