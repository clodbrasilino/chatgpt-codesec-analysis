#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

size_t count_repeated_items(const int *tuple, size_t length)
{
    size_t repeated_count = 0;
    size_t i;
    size_t j;

    if (tuple == NULL || length == 0) {
        return 0;
    }

    for (i = 0; i < length; i++) {
        bool seen_before = false;
        bool has_duplicate = false;

        for (j = 0; j < i; j++) {
            if (tuple[j] == tuple[i]) {
                seen_before = true;
                break;
            }
        }

        if (seen_before) {
            continue;
        }

        for (j = i + 1; j < length; j++) {
            if (tuple[j] == tuple[i]) {
                has_duplicate = true;
                break;
            }
        }

        if (has_duplicate) {
            repeated_count++;
        }
    }

    return repeated_count;
}

int main(void)
{
    const int tuple[] = {2, 4, 5, 4, 6, 2, 7, 5, 5};
    const size_t length = sizeof(tuple) / sizeof(tuple[0]);
    size_t result;

    result = count_repeated_items(tuple, length);

    if (printf("Number of repeated items: %zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}