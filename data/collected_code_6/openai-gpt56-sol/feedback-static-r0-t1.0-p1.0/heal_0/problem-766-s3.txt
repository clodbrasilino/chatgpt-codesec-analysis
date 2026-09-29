#include <stdio.h>
#include <stdlib.h>

static void print_consecutive_pairs(const int *items, size_t count)
{
    if (items == NULL || count < 2U) {
        return;
    }

    for (size_t i = 0U; i + 1U < count; ++i) {
        if (printf("(%d, %d)\n", items[i], items[i + 1U]) < 0) {
            return;
        }
    }
}

int main(void)
{
    const int items[] = {1, 2, 3, 4, 5};
    const size_t count = sizeof(items) / sizeof(items[0]);

    print_consecutive_pairs(items, count);

    if (ferror(stdout) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}