#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static void reverse_range(int list[], size_t first, size_t last)
{
    while (first < last) {
        int temporary = list[first];
        list[first] = list[last];
        list[last] = temporary;
        ++first;
        --last;
    }
}

bool rotate_right(int list[], size_t length, size_t positions)
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

    reverse_range(list, 0U, length - 1U);
    reverse_range(list, 0U, positions - 1U);
    reverse_range(list, positions, length - 1U);

    return true;
}

int main(void)
{
    int list[] = {1, 2, 3, 4, 5, 6, 7};
    const size_t length = sizeof(list) / sizeof(list[0]);
    const size_t positions = 3U;

    if (!rotate_right(list, length, positions)) {
        return EXIT_FAILURE;
    }

    for (size_t index = 0U; index < length; ++index) {
        if (printf("%d%s", list[index], index + 1U < length ? " " : "\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}