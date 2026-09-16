#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool contains_element(const int *list, size_t length, int element)
{
    if (list == NULL && length != 0U) {
        return false;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (list[i] == element) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    const int list[] = {3, 7, 11, 15, 19};
    const size_t length = sizeof list / sizeof list[0];
    const int element = 11;

    if (contains_element(list, length, element)) {
        puts("Element found.");
    } else {
        puts("Element not found.");
    }

    return 0;
}