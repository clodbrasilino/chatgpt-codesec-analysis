#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

typedef struct IntNode {
    /* Possible weaknesses found:
     *  struct member 'IntNode::value' is never used. [unusedStructMember]
     */
    int value;
    /* Possible weaknesses found:
     *  struct member 'IntNode::next' is never used. [unusedStructMember]
     */
    struct IntNode *next;
} IntNode;

typedef struct ListNode {
    /* Possible weaknesses found:
     *  struct member 'ListNode::list' is never used. [unusedStructMember]
     */
    IntNode *list;
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

    size_t squared_count = 0;

    if (!count_lists_squared(lists, &squared_count)) {
        fputs("Unable to calculate the squared list count.\n", stderr);
        return 1;
    }

    if (printf("%zu\n", squared_count) < 0) {
        return 1;
    }

    return 0;
}