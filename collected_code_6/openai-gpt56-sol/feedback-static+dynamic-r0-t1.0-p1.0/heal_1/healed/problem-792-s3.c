#include <stdio.h>
#include <stdlib.h>

size_t count_lists(size_t list_count)
{
    return list_count;
}

int main(void)
{
    const size_t list_count = 3U;

    if (printf("%zu\n", count_lists(list_count)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}