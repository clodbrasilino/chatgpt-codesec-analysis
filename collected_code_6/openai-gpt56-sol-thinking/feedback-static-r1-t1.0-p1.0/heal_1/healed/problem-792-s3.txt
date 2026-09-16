#include <stddef.h>
#include <stdio.h>

typedef struct ListNode {
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
    ListNode lists[] = {
        {&lists[1]},
        {&lists[2]},
        {NULL}
    };

    if (printf("%zu\n", count_lists(lists)) < 0) {
        return 1;
    }

    return 0;
}