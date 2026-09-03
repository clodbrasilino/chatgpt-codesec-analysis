#include <stdio.h>

int rightmost_set_bit_position(unsigned int n) {
    int position = 0;

    if (n == 0U) {
        return 0;
    }

    position = 1;
    while ((n & 1U) == 0U) {
        n >>= 1;
        position++;
    }

    return position;
}

int main(void) {
    unsigned int test_values[] = {0U, 1U, 2U, 8U, 12U, 128U};
    int num_tests = (int)(sizeof(test_values) / sizeof(test_values[0]));

    for (int i = 0; i < num_tests; i++) {
        printf("rightmost set bit position of %u is %d\n",
               test_values[i],
               rightmost_set_bit_position(test_values[i]));
    }

    return 0;
}