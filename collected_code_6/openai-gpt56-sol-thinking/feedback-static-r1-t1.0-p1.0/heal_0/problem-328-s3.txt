#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static void reverse_range(int *list, size_t first, size_t last)
{
    while (first < last) {
        int temporary = list[first];
        list[first] = list[last];
        list[last] = temporary;
        ++first;
        --last;
    }
}

static bool rotate_left(int *list, size_t length, size_t positions)
{
    if (length == 0U) {
        return true;
    }

    if (list == NULL) {
        return false;
    }

    positions %= length;

    if (positions == 0U) {
        return true;
    }

    reverse_range(list, 0U, positions - 1U);
    reverse_range(list, positions, length - 1U);
    reverse_range(list, 0U, length - 1U);

    return true;
}

static bool print_list(const int *list, size_t length)
{
    if (list == NULL && length != 0U) {
        return false;
    }

    for (size_t index = 0U; index < length; ++index) {
        if (printf("%d%s", list[index], index + 1U < length ? " " : "\n") < 0) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    int list[] = {1, 2, 3, 4, 5, 6, 7};
    const size_t length = sizeof(list) / sizeof(list[0]);
    const size_t positions = 3U;

    if (!rotate_left(list, length, positions)) {
        return 1;
    }

    if (!print_list(list, length)) {
        return 1;
    }

    return 0;
}