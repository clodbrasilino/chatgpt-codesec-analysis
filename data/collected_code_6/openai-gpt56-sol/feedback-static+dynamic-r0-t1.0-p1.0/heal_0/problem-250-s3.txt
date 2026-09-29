#include <stdio.h>
#include <stdlib.h>

static size_t count_occurrences(const int *tuple, size_t length, int element)
{
    size_t count = 0;

    if (tuple == NULL && length != 0) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        if (tuple[i] == element) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    const int tuple[] = {1, 2, 3, 2, 4, 2, 5};
    const size_t length = sizeof(tuple) / sizeof(tuple[0]);
    const int element = 2;
    const size_t count = count_occurrences(tuple, length, element);

    if (printf("%d occurs %zu times\n", element, count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}