#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static bool interchange_first_last(int *list, size_t length)
{
    int temporary;

    if (list == NULL || length == 0U) {
        return false;
    }

    if (length == 1U) {
        return true;
    }

    temporary = list[0];
    list[0] = list[length - 1U];
    list[length - 1U] = temporary;

    return true;
}

static bool print_list(const int *list, size_t length)
{
    size_t index;

    if (list == NULL || length == 0U) {
        return false;
    }

    for (index = 0U; index < length; ++index) {
        if (printf("%s%d", index == 0U ? "" : " ", list[index]) < 0) {
            return false;
        }
    }

    return putchar('\n') != EOF;
}

int main(void)
{
    int list[] = {10, 20, 30, 40, 50};
    const size_t length = sizeof(list) / sizeof(list[0]);

    if (!interchange_first_last(list, length)) {
        return EXIT_FAILURE;
    }

    if (!print_list(list, length)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}