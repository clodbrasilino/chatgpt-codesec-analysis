#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int value;
    struct ListNode *next;
} ListNode;

typedef enum {
    LIST_SUCCESS,
    LIST_INVALID_ARGUMENT,
    LIST_ALLOCATION_FAILURE,
    LIST_INTEGER_OVERFLOW
} ListStatus;

static void list_free(ListNode *head)
{
    while (head != NULL) {
        ListNode *next = head->next;
        free(head);
        head = next;
    }
}

static ListStatus list_from_array(const int *values, size_t count, ListNode **result)
{
    ListNode *head = NULL;
    ListNode **tail = &head;

    if (result == NULL || (values == NULL && count != 0U)) {
        return LIST_INVALID_ARGUMENT;
    }

    *result = NULL;

    for (size_t index = 0U; index < count; ++index) {
        ListNode *node = malloc(sizeof(*node));

        if (node == NULL) {
            list_free(head);
            return LIST_ALLOCATION_FAILURE;
        }

        node->value = values[index];
        node->next = NULL;
        *tail = node;
        tail = &node->next;
    }

    *result = head;
    return LIST_SUCCESS;
}

static ListStatus list_add(const ListNode *first, const ListNode *second,
                           ListNode **result)
{
    ListNode *head = NULL;
    ListNode **tail = &head;

    if (result == NULL) {
        return LIST_INVALID_ARGUMENT;
    }

    *result = NULL;

    while (first != NULL || second != NULL) {
        const int first_value = first != NULL ? first->value : 0;
        const int second_value = second != NULL ? second->value : 0;
        ListNode *node;

        if ((second_value > 0 && first_value > INT_MAX - second_value) ||
            (second_value < 0 && first_value < INT_MIN - second_value)) {
            list_free(head);
            return LIST_INTEGER_OVERFLOW;
        }

        node = malloc(sizeof(*node));
        if (node == NULL) {
            list_free(head);
            return LIST_ALLOCATION_FAILURE;
        }

        node->value = first_value + second_value;
        node->next = NULL;
        *tail = node;
        tail = &node->next;

        if (first != NULL) {
            first = first->next;
        }

        if (second != NULL) {
            second = second->next;
        }
    }

    *result = head;
    return LIST_SUCCESS;
}

static int list_print(const ListNode *head)
{
    if (fputc('[', stdout) == EOF) {
        return -1;
    }

    while (head != NULL) {
        if (printf("%d", head->value) < 0) {
            return -1;
        }

        if (head->next != NULL && fputs(", ", stdout) == EOF) {
            return -1;
        }

        head = head->next;
    }

    return fputs("]\n", stdout) == EOF ? -1 : 0;
}

int main(void)
{
    const int first_values[] = {1, 2, 3, 4};
    const int second_values[] = {5, 6, 7, 8};
    ListNode *first = NULL;
    ListNode *second = NULL;
    ListNode *sum = NULL;
    ListStatus status;
    int exit_status = EXIT_FAILURE;

    status = list_from_array(first_values,
                             sizeof(first_values) / sizeof(first_values[0]),
                             &first);
    if (status != LIST_SUCCESS) {
        goto cleanup;
    }

    status = list_from_array(second_values,
                             sizeof(second_values) / sizeof(second_values[0]),
                             &second);
    if (status != LIST_SUCCESS) {
        goto cleanup;
    }

    status = list_add(first, second, &sum);
    if (status != LIST_SUCCESS) {
        goto cleanup;
    }

    if (list_print(sum) != 0 || fflush(stdout) == EOF) {
        goto cleanup;
    }

    exit_status = EXIT_SUCCESS;

cleanup:
    list_free(sum);
    list_free(second);
    list_free(first);
    return exit_status;
}