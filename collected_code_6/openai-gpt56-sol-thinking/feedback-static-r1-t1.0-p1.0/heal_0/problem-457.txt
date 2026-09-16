#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const int *items;
    size_t length;
} Sublist;

const Sublist *find_minimum_length_sublist(const Sublist *sublists,
                                           size_t count)
{
    const Sublist *shortest;

    if (sublists == NULL || count == 0U) {
        return NULL;
    }

    shortest = &sublists[0];

    for (size_t i = 0U; i < count; ++i) {
        if (sublists[i].items == NULL && sublists[i].length != 0U) {
            return NULL;
        }

        if (sublists[i].length < shortest->length) {
            shortest = &sublists[i];
        }
    }

    return shortest;
}

bool print_sublist(const Sublist *sublist)
{
    if (sublist == NULL ||
        (sublist->items == NULL && sublist->length != 0U)) {
        return false;
    }

    if (fputc('[', stdout) == EOF) {
        return false;
    }

    for (size_t i = 0U; i < sublist->length; ++i) {
        if (i != 0U && fputs(", ", stdout) == EOF) {
            return false;
        }

        if (printf("%d", sublist->items[i]) < 0) {
            return false;
        }
    }

    return fputs("]\n", stdout) != EOF;
}

int main(void)
{
    static const int first[] = {1, 2, 3, 4};
    static const int second[] = {5, 6};
    static const int third[] = {7, 8, 9};

    static const Sublist sublists[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])}
    };

    const Sublist *shortest = find_minimum_length_sublist(
        sublists,
        sizeof(sublists) / sizeof(sublists[0])
    );

    if (shortest == NULL) {
        return EXIT_FAILURE;
    }

    if (!print_sublist(shortest)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}