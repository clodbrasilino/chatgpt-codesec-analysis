#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static bool all_items_equal(const char *const items[], size_t count,
                            const char *expected)
{
    size_t i;

    if (expected == NULL || (count > 0U && items == NULL)) {
        return false;
    }

    for (i = 0U; i < count; ++i) {
        if (items[i] == NULL || strcmp(items[i], expected) != 0) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const char *items[] = {"apple", "apple", "apple"};
    const size_t count = sizeof(items) / sizeof(items[0]);
    const char *expected = "apple";

    if (all_items_equal(items, count, expected)) {
        if (puts("All items are equal to the given string.") == EOF) {
            return 1;
        }
    } else {
        if (puts("Not all items are equal to the given string.") == EOF) {
            return 1;
        }
    }

    return 0;
}