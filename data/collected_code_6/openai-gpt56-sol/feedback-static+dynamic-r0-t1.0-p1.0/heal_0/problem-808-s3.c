#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static bool contains_k(const int *tuple, size_t tuple_size, int k)
{
    if (tuple == NULL && tuple_size != 0U) {
        return false;
    }

    for (size_t i = 0U; i < tuple_size; ++i) {
        if (tuple[i] == k) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    int k = 0;
    size_t tuple_count = 0U;

    if (scanf("%d %zu", &k, &tuple_count) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < tuple_count; ++i) {
        size_t tuple_size = 0U;

        if (scanf("%zu", &tuple_size) != 1) {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        bool found = false;

        for (size_t j = 0U; j < tuple_size; ++j) {
            int value = 0;

            if (scanf("%d", &value) != 1) {
                fputs("Invalid input\n", stderr);
                return EXIT_FAILURE;
            }

            if (contains_k(&value, 1U, k)) {
                found = true;
            }
        }

        puts(found ? "true" : "false");
    }

    return EXIT_SUCCESS;
}