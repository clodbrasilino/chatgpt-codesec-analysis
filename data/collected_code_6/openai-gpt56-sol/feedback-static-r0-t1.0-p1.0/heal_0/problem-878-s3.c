#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool tuple_contains_only_k_elements(size_t tuple_length, size_t k)
{
    return tuple_length == k;
}

int main(void)
{
    const int tuple[] = {1, 2, 3, 4};
    const size_t tuple_length = sizeof tuple / sizeof tuple[0];
    const size_t k = 4;

    if (printf("%s\n",
               tuple_contains_only_k_elements(tuple_length, k)
                   ? "true"
                   : "false") < 0) {
        return 1;
    }

    return 0;
}