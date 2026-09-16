#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool tuple_contains(const int *tuple, size_t length, int element)
{
    if (tuple == NULL && length != 0U) {
        return false;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (tuple[i] == element) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    const int tuple[] = {10, 20, 30, 40, 50};
    const size_t length = sizeof tuple / sizeof tuple[0];
    const int element = 30;

    if (tuple_contains(tuple, length, element)) {
        if (printf("%d exists in the tuple.\n", element) < 0) {
            return 1;
        }
    } else {
        if (printf("%d does not exist in the tuple.\n", element) < 0) {
            return 1;
        }
    }

    return 0;
}