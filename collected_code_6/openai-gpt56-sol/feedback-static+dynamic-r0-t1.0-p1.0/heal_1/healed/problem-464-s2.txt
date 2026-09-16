#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool all_values_same(const int *values, size_t count)
{
    if (count == 0U) {
        return true;
    }

    if (values == NULL) {
        return false;
    }

    for (size_t i = 1U; i < count; ++i) {
        if (values[i] != values[0]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const int values[] = {42, 42, 42};
    const size_t count = sizeof values / sizeof values[0];

    if (printf("%s\n", all_values_same(values, count) ? "true" : "false") < 0) {
        return 1;
    }

    return 0;
}