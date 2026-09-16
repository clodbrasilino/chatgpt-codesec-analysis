#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool contains(const int *list, size_t length, int value)
{
    if (list == NULL && length != 0U) {
        return false;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (list[i] == value) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    const int list[] = {4, 8, 15, 16, 23, 42};
    const size_t length = sizeof list / sizeof list[0];
    const int value = 15;

    if (contains(list, length, value)) {
        if (printf("%d is present\n", value) < 0) {
            return 1;
        }
    } else {
        if (printf("%d is not present\n", value) < 0) {
            return 1;
        }
    }

    return 0;
}