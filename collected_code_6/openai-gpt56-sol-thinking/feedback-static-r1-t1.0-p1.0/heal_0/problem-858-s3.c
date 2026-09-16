#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct IntNode {
    int value;
    const struct IntNode *next;
} IntNode;

typedef struct ListNode {
    const IntNode *list;
    const struct ListNode *next;
} ListNode;

static bool contains_cycle(const ListNode *lists)
{
    const ListNode *slow = lists;
    const ListNode *fast = lists;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return true;
        }
    }

    return false;
}

bool square_list_count(const ListNode *lists, size_t *squared_count)
{
    size_t count = 0U;
    const ListNode *current = lists;

    if (squared_count == NULL) {
        return false;
    }

    *squared_count = 0U;

    if (contains_cycle(lists)) {
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
    const IntNode third_inner = {5, NULL};
    const IntNode second_inner_tail = {4, NULL};
    const IntNode second_inner_head = {3, &second_inner_tail};
    const IntNode first_inner_tail = {2, NULL};
    const IntNode first_inner_head = {1, &first_inner_tail};

    const ListNode third_list = {&third_inner, NULL};
    const ListNode second_list = {&second_inner_head, &third_list};
    const ListNode first_list = {&first_inner_head, &second_list};

    size_t result = 0U;

    if (!square_list_count(&first_list, &result)) {
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