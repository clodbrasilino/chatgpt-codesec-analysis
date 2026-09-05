#include <stdio.h>
#include <stdint.h>
#include <limits.h>

static uint32_t next_power_of_two(uint32_t n)
{
    if (n == 0U) {
        return 1U;
    }

    if (n > (UINT32_MAX / 2U) + 1U) {
        return 0U;
    }

    n--;
    n |= n >> 1U;
    n |= n >> 2U;
    n |= n >> 4U;
    n |= n >> 8U;
    n |= n >> 16U;
    n++;

    return n;
}

int main(void)
{
    uint32_t test_values[] = {0U, 1U, 2U, 3U, 4U, 5U, 16U, 17U, 100U, 1000U};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'result' can be reduced. [variableScope]
     */
    uint32_t result;

    for (i = 0U; i < num_tests; i++) {
        result = next_power_of_two(test_values[i]);
        if (result == 0U) {
            (void)printf("next_power_of_two(%u) = overflow\n", test_values[i]);
        } else {
            (void)printf("next_power_of_two(%u) = %u\n", test_values[i], result);
        }
    }

    return 0;
}