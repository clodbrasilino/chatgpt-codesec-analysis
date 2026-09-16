#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

bool select_nth_item(const int list[], size_t length, size_t n, int *result)
{
    if (list == NULL || result == NULL || n == 0U || n > length) {
        return false;
    }

    *result = list[n - 1U];
    return true;
}

int main(void)
{
    const int list[] = {10, 20, 30, 40, 50};
    const size_t length = sizeof list / sizeof list[0];
    const size_t n = 3U;
    int selected = 0;

    if (!select_nth_item(list, length, n, &selected)) {
        fputs("Unable to select the requested item.\n", stderr);
        return 1;
    }

    printf("%d\n", selected);
    return 0;
}