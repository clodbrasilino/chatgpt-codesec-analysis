#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int value;
    struct ListNode *next;
} ListNode;

typedef enum {
    LIST_OK,
    LIST_INVALID_ARGUMENT,
    LIST_LENGTH_MISMATCH,
    LIST_ARITHMETIC_OVERFLOW,
    LIST_ALLOCATION_FAILURE
} ListStatus;

static void list_destroy(ListNode *head)
{
    while (head != NULL) {
        ListNode *next = head->next;
        free(head);
        head = next;
    }
}

static ListStatus list_from_array(const int values[], size_t count, ListNode **result)
{
    ListNode *head = NULL;
    ListNode *tail = NULL;
    size_t i;

    if (result == NULL || *result != NULL || (count > 0U && values == NULL)) {
        return LIST_INVALID_ARGUMENT;
    }

    for (i = 0U; i < count; ++i) {
        ListNode *node = malloc(sizeof(*node));

        if (node == NULL) {
            list_destroy(head);
            return LIST_ALLOCATION_FAILURE;
        }

        node->value = values[i];
        node->next = NULL;

        if (tail == NULL) {
            head = node;
        } else {
            tail->next = node;
        }

        tail = node;
    }

    *result = head;
    return LIST_OK;
}

static ListStatus list_subtract(const ListNode *first,
                                const ListNode *second,
                                ListNode **result)
{
    ListNode *head = NULL;
    ListNode *tail = NULL;

    if (result == NULL || *result != NULL) {
        return LIST_INVALID_ARGUMENT;
    }

    while (first != NULL && second != NULL) {
        ListNode *node;
        int difference;

        if ((second->value > 0 &&
             first->value < INT_MIN + second->value) ||
            (second->value < 0 &&
             first->value > INT_MAX + second->value)) {
            list_destroy(head);
            return LIST_ARITHMETIC_OVERFLOW;
        }

        difference = first->value - second->value;
        node = malloc(sizeof(*node));

        if (node == NULL) {
            list_destroy(head);
            return LIST_ALLOCATION_FAILURE;
        }

        node->value = difference;
        node->next = NULL;

        if (tail == NULL) {
            head = node;
        } else {
            tail->next = node;
        }

        tail = node;
        first = first->next;
        second = second->next;
    }

    if (first != NULL || second != NULL) {
        list_destroy(head);
        return LIST_LENGTH_MISMATCH;
    }

    *result = head;
    return LIST_OK;
}

static bool list_print(const ListNode *head)
{
    if (putchar('[') == EOF) {
        return false;
    }

    while (head != NULL) {
        if (printf("%d", head->value) < 0) {
            return false;
        }

        head = head->next;

        if (head != NULL && fputs(", ", stdout) == EOF) {
            return false;
        }
    }

    return fputs("]\n", stdout) != EOF;
}

int main(void)
{
    const int first_values[] = {20, 15, 10, 5};
    const int second_values[] = {5, 7, 3, 2};
    ListNode *first = NULL;
    ListNode *second = NULL;
    ListNode *result = NULL;
    ListStatus status;
    int exit_status = EXIT_FAILURE;

    status = list_from_array(
        first_values,
        sizeof(first_values) / sizeof(first_values[0]),
        &first
    );
    if (status != LIST_OK) {
        goto cleanup;
    }

    status = list_from_array(
        second_values,
        sizeof(second_values) / sizeof(second_values[0]),
        &second
    );
    if (status != LIST_OK) {
        goto cleanup;
    }

    status = list_subtract(first, second, &result);
    if (status != LIST_OK) {
        goto cleanup;
    }

    if (!list_print(result)) {
        goto cleanup;
    }

    exit_status = EXIT_SUCCESS;

cleanup:
    list_destroy(result);
    list_destroy(second);
    list_destroy(first);
    return exit_status;
}