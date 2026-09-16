#include <stdio.h>
#include <stddef.h>

static size_t count_odd_rotations(const char *str)
{
    size_t count = 0;
    size_t i;

    if (str == NULL) {
        return 0;
    }

    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == '1') {
            count++;
        }
    }

    return count;
}

int main(void)
{
    const char *tests[] = { "011001", "11011", "1010", "0000", "1111" };
    size_t num_tests = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < num_tests; i++) {
        size_t result = count_odd_rotations(tests[i]);
        if (printf("String: %s -> Odd rotations: %zu\n", tests[i], result) < 0) {
            return 1;
        }
    }

    return 0;
}