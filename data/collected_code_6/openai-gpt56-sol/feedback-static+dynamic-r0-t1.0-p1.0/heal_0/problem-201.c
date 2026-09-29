#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool all_elements_same(const int *list, size_t count)
{
    if (list == NULL || count == 0U) {
        return false;
    }

    for (size_t i = 1U; i < count; ++i) {
        if (list[i] != list[0]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const int list[] = {5, 5, 5, 5, 5};
    const size_t count = sizeof list / sizeof list[0];

    if (all_elements_same(list, count)) {
        if (puts("All elements are the same.") == EOF) {
            return 1;
        }
    } else {
        if (puts("The elements are not all the same.") == EOF) {
            return 1;
        }
    }

    return 0;
}