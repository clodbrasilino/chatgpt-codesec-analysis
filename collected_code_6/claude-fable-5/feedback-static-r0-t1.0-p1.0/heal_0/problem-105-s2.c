#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

size_t count_true(const bool *list, size_t length)
{
    size_t count = 0;

    if (list == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; i++) {
        if (list[i]) {
            count++;
        }
    }

    return count;
}

int main(void)
{
    bool values[] = { true, false, true, true, false, true };
    size_t length = sizeof(values) / sizeof(values[0]);

    size_t result = count_true(values, length);

    if (printf("Number of true values: %zu\n", result) < 0) {
        return 1;
    }

    return 0;
}