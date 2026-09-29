#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const int *items;
    size_t length;
} IntList;

typedef struct ListNode {
    const IntList *list;
    const struct ListNode *next;
} ListNode;

bool count_lists_and_square(const ListNode *head, size_t *result)
{
    const ListNode *slow = head;
    const ListNode *fast = head;
    const ListNode *current;
    size_t count = 0U;

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

    for (current = head; current != NULL; current = current->next) {
        if (current->list == NULL ||
            (current->list->length > 0U && current->list->items == NULL)) {
            return false;
        }

        if (count == SIZE_MAX) {
            return false;
        }

        ++count;
    }

    if (count != 0U && count > SIZE_MAX / count) {
        return false;
    }

    *result = count * count;
    return true;
}

int main(void)
{
    const int first_items[] = {1, 2, 3};
    const int second_items[] = {4, 5};
    const int third_items[] = {6};

    const IntList first_list = {first_items, 3U};
    const IntList second_list = {second_items, 2U};
    const IntList third_list = {third_items, 1U};

    const ListNode third_node = {&third_list, NULL};
    const ListNode second_node = {&second_list, &third_node};
    const ListNode first_node = {&first_list, &second_node};

    size_t squared_count;

    if (!count_lists_and_square(&first_node, &squared_count)) {
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", squared_count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}