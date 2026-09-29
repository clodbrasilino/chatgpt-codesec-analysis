#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool contains_sublist(const int *list, size_t list_length,
                             const int *sublist, size_t sublist_length)
{
    if (sublist_length == 0U) {
        return true;
    }

    if (list == NULL || sublist == NULL || sublist_length > list_length) {
        return false;
    }

    for (size_t i = 0U; i <= list_length - sublist_length; ++i) {
        size_t j = 0U;

        while (j < sublist_length && list[i + j] == sublist[j]) {
            ++j;
        }

        if (j == sublist_length) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    const int list[] = {1, 2, 3, 4, 5, 6};
    const int sublist[] = {3, 4, 5};
    const size_t list_length = sizeof(list) / sizeof(list[0]);
    const size_t sublist_length = sizeof(sublist) / sizeof(sublist[0]);

    const bool found = contains_sublist(list, list_length,
                                        sublist, sublist_length);

    if (printf("%s\n", found ? "Sublist found" : "Sublist not found") < 0) {
        return 1;
    }

    return 0;
}