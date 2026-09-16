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
    const int list[] = {4, 8, 15, 16, 23, 42};
    const size_t length = sizeof list / sizeof list[0];
    const int element = 15;

    if (contains_element(list, length, element)) {
        if (printf("%d is present\n", element) < 0) {
            return 1;
        }
    } else {
        if (printf("%d is not present\n", element) < 0) {
            return 1;
        }
    }

    return 0;
}