#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool even_indices_contain_even_numbers(const int values[], size_t length)
{
    if (values == NULL && length != 0U) {
        return false;
    }

    for (size_t index = 0U; index < length; index += 2U) {
        if (values[index] % 2 != 0) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const int values[] = {2, 3, 4, 7, 6, 9};
    const size_t length = sizeof(values) / sizeof(values[0]);

    if (even_indices_contain_even_numbers(values, length)) {
        printf("Every even index contains an even number.\n");
    } else {
        printf("Not every even index contains an even number.\n");
    }

    return 0;
}