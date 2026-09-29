#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    const int *items;
    size_t length;
} Sublist;

const Sublist *find_minimum_length_sublist(const Sublist *sublists, size_t count)
{
    const Sublist *minimum;

    if (sublists == NULL || count == 0U) {
        return NULL;
    }

    minimum = &sublists[0];

    for (size_t i = 0U; i < count; ++i) {
        if (sublists[i].items == NULL && sublists[i].length != 0U) {
            return NULL;
        }

        if (sublists[i].length < minimum->length) {
            minimum = &sublists[i];
        }
    }

    return minimum;
}

int main(void)
{
    const int first[] = {1, 2, 3, 4};
    const int second[] = {5, 6};
    const int third[] = {7, 8, 9};
    const Sublist sublists[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])}
    };
    const size_t count = sizeof(sublists) / sizeof(sublists[0]);
    const Sublist *minimum = find_minimum_length_sublist(sublists, count);

    if (minimum == NULL) {
        return EXIT_FAILURE;
    }

    if (printf("Minimum-length sublist:") < 0) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < minimum->length; ++i) {
        if (printf(" %d", minimum->items[i]) < 0) {
            return EXIT_FAILURE;
        }
    }

    if (printf("\nLength: %zu\n", minimum->length) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}