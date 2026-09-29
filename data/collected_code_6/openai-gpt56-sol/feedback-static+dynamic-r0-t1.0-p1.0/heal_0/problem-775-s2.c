#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool odd_indices_contain_odd_numbers(const int values[], size_t length)
{
    if (values == NULL && length != 0U) {
        return false;
    }

    for (size_t index = 1U; index < length; index += 2U) {
        if (values[index] % 2 == 0) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const int values[] = {2, 3, 4, 5, 6, 7};
    const size_t length = sizeof(values) / sizeof(values[0]);

    if (odd_indices_contain_odd_numbers(values, length)) {
        if (puts("Every odd index contains an odd number.") == EOF) {
            return 1;
        }
    } else {
        if (puts("Not every odd index contains an odd number.") == EOF) {
            return 1;
        }
    }

    return 0;
}