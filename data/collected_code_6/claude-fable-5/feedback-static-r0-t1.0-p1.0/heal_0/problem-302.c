#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_msb_position(unsigned int value)
{
    int position = -1;

    while (value != 0U) {
        value >>= 1U;
        position++;
    }

    return position;
}

int main(void)
{
    unsigned int test_values[] = { 0U, 1U, 2U, 5U, 128U, 1024U, UINT_MAX };
    size_t count = sizeof(test_values) / sizeof(test_values[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        int msb = find_msb_position(test_values[i]);

        if (msb < 0) {
            if (printf("Value %u has no set bits\n", test_values[i]) < 0) {
                return EXIT_FAILURE;
            }
        } else {
            if (printf("Value %u: most significant set bit is at position %d\n",
                       test_values[i], msb) < 0) {
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}