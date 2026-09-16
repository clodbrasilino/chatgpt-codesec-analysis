#include <stddef.h>
#include <stdio.h>

static size_t count_even(const int *list, size_t length)
{
    size_t count = 0;

    if (list == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        if (list[i] % 2 == 0) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    const int list[] = {1, 2, 3, 4, 5, 6, 8};
    const size_t length = sizeof(list) / sizeof(list[0]);
    const size_t even_count = count_even(list, length);

    if (printf("%zu\n", even_count) < 0) {
        return 1;
    }

    return 0;
}