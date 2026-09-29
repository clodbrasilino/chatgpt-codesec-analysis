#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    unsigned int digit;
    struct ListNode *next;
} ListNode;

static void free_list(ListNode *head)
{
    while (head != NULL) {
        ListNode *next = head->next;
        free(head);
        head = next;
    }
}

static bool is_valid_list(const ListNode *head)
{
    const ListNode *slow = head;
    const ListNode *fast = head;
    const ListNode *current;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return false;
        }
    }

    for (current = head; current != NULL; current = current->next) {
        if (current->digit > 9U) {
            return false;
        }
    }

    return true;
}

static bool append_digit(ListNode **head, ListNode **tail, unsigned int digit)
{
    ListNode *node;

    if (head == NULL || tail == NULL || digit > 9U) {
        return false;
    }

    node = malloc(sizeof(*node));
    if (node == NULL) {
        return false;
    }

    node->digit = digit;
    node->next = NULL;

    if (*tail == NULL) {
        *head = node;
    } else {
        (*tail)->next = node;
    }

    *tail = node;
    return true;
}

bool add_lists(const ListNode *first, const ListNode *second, ListNode **result)
{
    ListNode *head = NULL;
    ListNode *tail = NULL;
    unsigned int carry = 0U;

    if (result == NULL) {
        return false;
    }

    *result = NULL;

    if (!is_valid_list(first) || !is_valid_list(second)) {
        return false;
    }

    do {
        unsigned int sum = carry;

        if (first != NULL) {
            sum += first->digit;
            first = first->next;
        }

        if (second != NULL) {
            sum += second->digit;
            second = second->next;
        }

        if (!append_digit(&head, &tail, sum % 10U)) {
            free_list(head);
            return false;
        }

        carry = sum / 10U;
    } while (first != NULL || second != NULL || carry != 0U);

    *result = head;
    return true;
}

static bool create_list(const unsigned int digits[], size_t count, ListNode **result)
{
    ListNode *head = NULL;
    ListNode *tail = NULL;
    size_t i;

    if (result == NULL || (digits == NULL && count != 0U)) {
        return false;
    }

    *result = NULL;

    for (i = 0U; i < count; ++i) {
        if (!append_digit(&head, &tail, digits[i])) {
            free_list(head);
            return false;
        }
    }

    *result = head;
    return true;
}

static void print_list(const ListNode *head)
{
    const ListNode *current = head;

    while (current != NULL) {
        printf("%u", current->digit);

        if (current->next != NULL) {
            printf(" -> ");
        }

        current = current->next;
    }

    putchar('\n');
}

int main(void)
{
    const unsigned int first_digits[] = {2U, 4U, 3U};
    const unsigned int second_digits[] = {5U, 6U, 4U};
    ListNode *first = NULL;
    ListNode *second = NULL;
    ListNode *result = NULL;
    int status = EXIT_FAILURE;

    if (!create_list(first_digits,
                     sizeof(first_digits) / sizeof(first_digits[0]),
                     &first)) {
        fprintf(stderr, "Failed to create the first list.\n");
        goto cleanup;
    }

    if (!create_list(second_digits,
                     sizeof(second_digits) / sizeof(second_digits[0]),
                     &second)) {
        fprintf(stderr, "Failed to create the second list.\n");
        goto cleanup;
    }

    if (!add_lists(first, second, &result)) {
        fprintf(stderr, "Failed to add the lists.\n");
        goto cleanup;
    }

    print_list(result);
    status = EXIT_SUCCESS;

cleanup:
    free_list(result);
    free_list(second);
    free_list(first);
    return status;
}