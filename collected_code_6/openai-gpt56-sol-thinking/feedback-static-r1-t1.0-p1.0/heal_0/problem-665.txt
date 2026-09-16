#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool shift_first_to_end(int *list, size_t length)
{
    if (list == NULL && length > 0U) {
        return false;
    }

    if (length < 2U) {
        return true;
    }

    int first = list[0];

    for (size_t i = 1U; i < length; ++i) {
        list[i - 1U] = list[i];
    }

    list[length - 1U] = first;
    return true;
}

static bool print_list(const int *list, size_t length)
{
    if (list == NULL && length > 0U) {
        return false;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (printf("%d%s", list[i], i + 1U < length ? " " : "\n") < 0) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    int list[] = {1, 2, 3, 4, 5};
    const size_t length = sizeof(list) / sizeof(list[0]);

    if (!shift_first_to_end(list, length)) {
        fputs("Failed to shift the list.\n", stderr);
        return 1;
    }

    if (!print_list(list, length)) {
        fputs("Failed to print the list.\n", stderr);
        return 1;
    }

    return 0;
}