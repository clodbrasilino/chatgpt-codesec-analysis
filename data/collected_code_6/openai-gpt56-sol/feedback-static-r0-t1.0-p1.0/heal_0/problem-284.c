#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static bool all_equal_to(const char *const items[], size_t count,
                         const char *target)
{
    size_t i;

    if (target == NULL || (count > 0U && items == NULL)) {
        return false;
    }

    for (i = 0U; i < count; ++i) {
        if (items[i] == NULL || strcmp(items[i], target) != 0) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const char *const items[] = {"apple", "apple", "apple"};
    const char *target = "apple";
    const size_t count = sizeof(items) / sizeof(items[0]);

    if (all_equal_to(items, count, target)) {
        if (puts("All items are equal to the target string.") == EOF) {
            return 1;
        }
    } else {
        if (puts("Not all items are equal to the target string.") == EOF) {
            return 1;
        }
    }

    return 0;
}