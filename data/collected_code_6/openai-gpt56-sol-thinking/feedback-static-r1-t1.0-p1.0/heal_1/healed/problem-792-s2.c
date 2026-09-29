#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    struct List *next;
} List;

bool count_lists(const List *lists, size_t *count)
{
    const List *slow = lists;
    const List *fast = lists;
    size_t total = 0;

    if (count == NULL) {
        return false;
    }

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return false;
        }
    }

    while (lists != NULL) {
        if (total == SIZE_MAX) {
            return false;
        }

        ++total;
        lists = lists->next;
    }

    *count = total;
    return true;
}

int main(void)
{
    List lists[] = {
        {&lists[1]},
        {&lists[2]},
        {NULL}
    };
    size_t count;

    if (!count_lists(lists, &count)) {
        fputs("Unable to count lists.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}