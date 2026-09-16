#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool even_indices_contain_even_numbers(const int *list, size_t length)
{
    if (list == NULL && length != 0U) {
        return false;
    }

    for (size_t i = 0U; i < length; i += 2U) {
        if (list[i] % 2 != 0) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const int list[] = {2, 3, 4, 7, 6, 9};
    const size_t length = sizeof(list) / sizeof(list[0]);

    if (even_indices_contain_even_numbers(list, length)) {
        puts("Every even index contains an even number.");
    } else {
        puts("Not every even index contains an even number.");
    }

    return 0;
}