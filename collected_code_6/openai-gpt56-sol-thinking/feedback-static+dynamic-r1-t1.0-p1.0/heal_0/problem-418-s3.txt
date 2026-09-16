#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const int *items;
    size_t length;
} Sublist;

const Sublist *find_max_length_sublist(const Sublist *sublists, size_t count)
{
    const Sublist *longest;
    size_t i;

    if (sublists == NULL || count == 0) {
        return NULL;
    }

    longest = &sublists[0];

    for (i = 0; i < count; ++i) {
        if (sublists[i].length > 0 && sublists[i].items == NULL) {
            return NULL;
        }

        if (sublists[i].length > longest->length) {
            longest = &sublists[i];
        }
    }

    return longest;
}

static int print_sublist(const Sublist *sublist)
{
    size_t i;

    if (sublist == NULL ||
        (sublist->length > 0 && sublist->items == NULL)) {
        return -1;
    }

    if (printf("Maximum length: %zu\nSublist: [", sublist->length) < 0) {
        return -1;
    }

    for (i = 0; i < sublist->length; ++i) {
        if (printf("%s%d", i == 0 ? "" : ", ", sublist->items[i]) < 0) {
            return -1;
        }
    }

    if (puts("]") == EOF) {
        return -1;
    }

    return 0;
}

int main(void)
{
    static const int first[] = {1, 2, 3};
    static const int second[] = {4, 5, 6, 7, 8};
    static const int third[] = {9, 10};
    static const Sublist sublists[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])}
    };
    const Sublist *longest;

    longest = find_max_length_sublist(
        sublists,
        sizeof(sublists) / sizeof(sublists[0])
    );

    if (longest == NULL || print_sublist(longest) != 0) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}