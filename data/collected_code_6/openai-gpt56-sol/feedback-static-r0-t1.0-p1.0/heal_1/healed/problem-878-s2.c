#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool tuple_contains_only_k_elements(size_t tuple_size, size_t k)
{
    return tuple_size == k;
}

int main(void)
{
    int tuple[] = {1, 2, 3};
    size_t k = 0U;

    if (scanf("%zu", &k) != 1) {
        return 1;
    }

    const size_t tuple_size = sizeof tuple / sizeof tuple[0];
    const bool contains_only_k_elements =
        tuple_contains_only_k_elements(tuple_size, k);

    if (printf("%s\n", contains_only_k_elements ? "true" : "false") < 0) {
        return 1;
    }

    return 0;
}