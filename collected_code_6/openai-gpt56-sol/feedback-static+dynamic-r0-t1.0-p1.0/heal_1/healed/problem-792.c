#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int *items;
    size_t item_count;
} List;

static size_t count_items(const List *lists, size_t list_count)
{
    size_t total = 0U;

    if (lists == NULL) {
        return 0U;
    }

    for (size_t i = 0U; i < list_count; ++i) {
        if (lists[i].items != NULL) {
            total += lists[i].item_count;
        }
    }

    return total;
}

int main(void)
{
    int first_items[] = {1, 2};
    int second_items[] = {3, 4, 5};

    const List lists[] = {
        {first_items, sizeof(first_items) / sizeof(first_items[0])},
        {second_items, sizeof(second_items) / sizeof(second_items[0])},
        {NULL, 0U}
    };
    const size_t list_count = sizeof(lists) / sizeof(lists[0]);

    if (printf("%zu\n", count_items(lists, list_count)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}