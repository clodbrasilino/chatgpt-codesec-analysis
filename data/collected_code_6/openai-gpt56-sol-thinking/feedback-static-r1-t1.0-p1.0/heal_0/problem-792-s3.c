#include <stddef.h>
#include <stdio.h>

typedef struct IntNode {
    int value;
    struct IntNode *next;
} IntNode;

typedef struct ListNode {
    IntNode *list;
    struct ListNode *next;
} ListNode;

size_t count_lists(const ListNode *lists)
{
    size_t count = 0;

    while (lists != NULL) {
        ++count;
        lists = lists->next;
    }

    return count;
}

int main(void)
{
    IntNode first_values[] = {
        {1, &first_values[1]},
        {2, NULL}
    };
    IntNode second_values[] = {
        {3, NULL}
    };
    IntNode third_values[] = {
        {4, &third_values[1]},
        {5, &third_values[2]},
        {6, NULL}
    };
    ListNode lists[] = {
        {first_values, &lists[1]},
        {second_values, &lists[2]},
        {third_values, NULL}
    };

    if (printf("%zu\n", count_lists(lists)) < 0) {
        return 1;
    }

    return 0;
}