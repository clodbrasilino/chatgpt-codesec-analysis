#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

typedef struct ListNode {
    struct ListNode *next;
} ListNode;

static bool count_lists_squared(const ListNode *head, size_t *result)
{
    const ListNode *slow = head;
    const ListNode *fast = head;
    size_t count = 0;

    if (result == NULL) {
        return false;
    }

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return false;
        }
    }

    while (head != NULL) {
        if (count == SIZE_MAX) {
            return false;
        }

        ++count;
        head = head->next;
    }

    if (count != 0 && count > SIZE_MAX / count) {
        return false;
    }

    *result = count * count;
    return true;
}

int main(void)
{
    ListNode lists[] = {
        {&lists[1]},
        {&lists[2]},
        {NULL}
    };
    size_t squared_count;

    if (!count_lists_squared(lists, &squared_count)) {
        fputs("Unable to calculate the squared list count.\n", stderr);
        return 1;
    }

    if (printf("%zu\n", squared_count) < 0) {
        return 1;
    }

    return 0;
}