#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    const struct ListNode *next;
} ListNode;

static bool contains_cycle(const ListNode *head)
{
    const ListNode *slow = head;
    const ListNode *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return true;
        }
    }

    return false;
}

bool square_list_count(const ListNode *head, size_t *squared_count)
{
    size_t count = 0U;
    const ListNode *current = head;

    if (squared_count == NULL) {
        return false;
    }

    *squared_count = 0U;

    if (contains_cycle(head)) {
        return false;
    }

    while (current != NULL) {
        if (count == SIZE_MAX) {
            return false;
        }

        ++count;
        current = current->next;
    }

    if (count != 0U && count > SIZE_MAX / count) {
        return false;
    }

    *squared_count = count * count;
    return true;
}

int main(void)
{
    const ListNode third = {NULL};
    const ListNode second = {&third};
    const ListNode first = {&second};
    size_t result = 0U;

    if (!square_list_count(&first, &result)) {
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}