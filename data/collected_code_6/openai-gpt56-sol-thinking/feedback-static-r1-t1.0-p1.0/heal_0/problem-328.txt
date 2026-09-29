#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static void reverse_range(int *values, size_t first, size_t last)
{
    while (first < last) {
        int temporary;

        --last;
        if (first >= last) {
            break;
        }

        temporary = values[first];
        values[first] = values[last];
        values[last] = temporary;
        ++first;
    }
}

bool rotate_left(int *values, size_t count, size_t positions)
{
    if (values == NULL && count != 0U) {
        return false;
    }

    if (count < 2U) {
        return true;
    }

    positions %= count;
    if (positions == 0U) {
        return true;
    }

    reverse_range(values, 0U, positions);
    reverse_range(values, positions, count);
    reverse_range(values, 0U, count);

    return true;
}

int main(void)
{
    int values[] = {1, 2, 3, 4, 5, 6};
    const size_t count = sizeof(values) / sizeof(values[0]);
    const size_t positions = 2U;

    if (!rotate_left(values, count, positions)) {
        return EXIT_FAILURE;
    }

    for (size_t index = 0U; index < count; ++index) {
        if (printf("%d%s", values[index], index + 1U < count ? " " : "\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}