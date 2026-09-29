#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ListItem {
    int value;
    struct ListItem *next;
} ListItem;

typedef struct List {
    ListItem *head;
    struct List *next;
} List;

bool count_lists(const List *lists, size_t *count)
{
    const List *slow;
    const List *fast;
    size_t total = 0;

    if (count == NULL) {
        return false;
    }

    slow = lists;
    fast = lists;

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
    ListItem first_items[] = {
        {1, &first_items[1]},
        {2, NULL}
    };
    ListItem second_items[] = {
        {3, NULL}
    };
    List lists[] = {
        {first_items, &lists[1]},
        {second_items, &lists[2]},
        {NULL, NULL}
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