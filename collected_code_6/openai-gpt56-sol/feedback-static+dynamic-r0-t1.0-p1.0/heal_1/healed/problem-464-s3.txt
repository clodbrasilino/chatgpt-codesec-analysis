#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static bool all_values_are_same(const char *const values[], size_t count)
{
    if (values == NULL || count == 0 || values[0] == NULL) {
        return false;
    }

    for (size_t i = 1; i < count; ++i) {
        if (values[i] == NULL || strcmp(values[0], values[i]) != 0) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const char *const values[] = {
        "value",
        "value",
        "value"
    };
    const size_t count = sizeof values / sizeof values[0];

    const char *message = all_values_are_same(values, count)
        ? "All values are the same."
        : "Values are not all the same.";

    return puts(message) == EOF ? 1 : 0;
}