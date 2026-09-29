#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool even_indices_contain_even_numbers(const int list[], size_t length)
{
    if (list == NULL && length != 0U) {
        return false;
    }

    for (size_t index = 0U; index < length; index += 2U) {
        if (list[index] % 2 != 0) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const int list[] = {2, 7, 4, 9, 6, 11};
    const size_t length = sizeof list / sizeof list[0];

    if (even_indices_contain_even_numbers(list, length)) {
        if (puts("Every even index contains an even number.") == EOF) {
            return 1;
        }
    } else {
        if (puts("Not every even index contains an even number.") == EOF) {
            return 1;
        }
    }

    return 0;
}