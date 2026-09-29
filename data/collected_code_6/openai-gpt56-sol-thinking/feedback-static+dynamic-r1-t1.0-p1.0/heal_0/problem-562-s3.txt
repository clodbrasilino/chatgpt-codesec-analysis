#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const int *items;
    size_t length;
} Sublist;

bool find_maximum_sublist_length(const Sublist *sublists,
                                 size_t count,
                                 size_t *maximum_length)
{
    size_t maximum = 0;

    if (maximum_length == NULL || (count > 0 && sublists == NULL)) {
        return false;
    }

    for (size_t i = 0; i < count; ++i) {
        if (sublists[i].length > 0 && sublists[i].items == NULL) {
            return false;
        }

        if (sublists[i].length > maximum) {
            maximum = sublists[i].length;
        }
    }

    *maximum_length = maximum;
    return true;
}

int main(void)
{
    const int first[] = {1, 2, 3};
    const int second[] = {4, 5, 6, 7, 8};
    const int third[] = {9, 10};

    const Sublist sublists[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])}
    };

    size_t maximum_length = 0;
    const size_t count = sizeof(sublists) / sizeof(sublists[0]);

    if (!find_maximum_sublist_length(sublists, count, &maximum_length)) {
        fputs("Failed to find the maximum sublist length.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%zu\n", maximum_length);
    return EXIT_SUCCESS;
}