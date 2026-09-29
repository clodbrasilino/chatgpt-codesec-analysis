#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static void reverse_list(int *list, size_t start, size_t end)
{
    while (start < end) {
        int temporary = list[start];
        list[start] = list[end];
        list[end] = temporary;
        ++start;
        --end;
    }
}

bool rotate_right(int *list, size_t length, size_t positions)
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

    reverse_list(list, 0U, length - 1U);
    reverse_list(list, 0U, positions - 1U);
    reverse_list(list, positions, length - 1U);

    return true;
}

int main(void)
{
    int list[] = {1, 2, 3, 4, 5};
    const size_t length = sizeof(list) / sizeof(list[0]);
    const size_t positions = 2U;

    if (!rotate_right(list, length, positions)) {
        return 1;
    }

    for (size_t index = 0U; index < length; ++index) {
        if (printf("%d%s", list[index], index + 1U < length ? " " : "\n") < 0) {
            return 1;
        }
    }

    return 0;
}