#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool tuple_contains(const int *tuple, size_t length, int element)
{
    if (tuple == NULL) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        if (tuple[i] == element) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    const int tuple[] = {4, 8, 15, 16, 23, 42};
    const size_t length = sizeof(tuple) / sizeof(tuple[0]);
    const int element = 15;

    if (printf("%d\n", tuple_contains(tuple, length, element) ? 1 : 0) < 0) {
        return 1;
    }

    return 0;
}