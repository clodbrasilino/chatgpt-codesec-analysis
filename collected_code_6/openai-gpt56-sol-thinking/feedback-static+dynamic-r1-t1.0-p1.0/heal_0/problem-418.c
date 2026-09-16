#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const int *items;
    size_t length;
} Sublist;

static bool find_longest_sublist(const Sublist *sublists,
                                 size_t count,
                                 const Sublist **longest)
{
    size_t longest_index = 0;

    if (sublists == NULL || longest == NULL || count == 0) {
        return false;
    }

    *longest = NULL;

    for (size_t i = 0; i < count; ++i) {
        if (sublists[i].length > 0 && sublists[i].items == NULL) {
            return false;
        }

        if (sublists[i].length > sublists[longest_index].length) {
            longest_index = i;
        }
    }

    *longest = &sublists[longest_index];
    return true;
}

int main(void)
{
    const int first[] = {1, 2, 3};
    const int second[] = {4, 5, 6, 7, 8};
    const int third[] = {9, 10, 11, 12};

    const Sublist sublists[] = {
        {first, sizeof first / sizeof first[0]},
        {second, sizeof second / sizeof second[0]},
        {third, sizeof third / sizeof third[0]}
    };

    const Sublist *longest = NULL;
    const size_t count = sizeof sublists / sizeof sublists[0];

    if (!find_longest_sublist(sublists, count, &longest)) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < longest->length; ++i) {
        if (i > 0 && putchar(' ') == EOF) {
            return EXIT_FAILURE;
        }

        if (printf("%d", longest->items[i]) < 0) {
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}