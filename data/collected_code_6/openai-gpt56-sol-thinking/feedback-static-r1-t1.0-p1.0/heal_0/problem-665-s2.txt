#include <stdio.h>
#include <stddef.h>

static int shift_first_to_end(int *list, size_t length)
{
    int first;
    size_t i;

    if (list == NULL || length == 0U) {
        return -1;
    }

    first = list[0];

    for (i = 1U; i < length; ++i) {
        list[i - 1U] = list[i];
    }

    list[length - 1U] = first;
    return 0;
}

int main(void)
{
    int list[] = {1, 2, 3, 4, 5};
    const size_t length = sizeof(list) / sizeof(list[0]);
    size_t i;

    if (shift_first_to_end(list, length) != 0) {
        return 1;
    }

    for (i = 0U; i < length; ++i) {
        if (printf("%d%s", list[i], i + 1U < length ? " " : "\n") < 0) {
            return 1;
        }
    }

    return 0;
}