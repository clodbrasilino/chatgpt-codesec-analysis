#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef enum {
    LIST_SUCCESS = 0,
    LIST_INVALID_ARGUMENT,
    LIST_ALLOCATION_FAILURE,
    LIST_ARITHMETIC_OVERFLOW,
    LIST_OUTPUT_FAILURE
} ListStatus;

static void free_list(Node *head)
{
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

static ListStatus append_node(Node **head, Node **tail, int value)
{
    Node *node;

    if (head == NULL || tail == NULL) {
        return LIST_INVALID_ARGUMENT;
    }

    node = malloc(sizeof(*node));
    if (node == NULL) {
        return LIST_ALLOCATION_FAILURE;
    }

    node->value = value;
    node->next = NULL;

    if (*tail == NULL) {
        *head = node;
    } else {
        (*tail)->next = node;
    }

    *tail = node;
    return LIST_SUCCESS;
}

static ListStatus create_list(const int values[], size_t count, Node **result)
{
    Node *head = NULL;
    Node *tail = NULL;
    size_t index;

    if (result == NULL || (values == NULL && count != 0U)) {
        return LIST_INVALID_ARGUMENT;
    }

    *result = NULL;

    for (index = 0U; index < count; ++index) {
        ListStatus status = append_node(&head, &tail, values[index]);

        if (status != LIST_SUCCESS) {
            free_list(head);
            return status;
        }
    }

    *result = head;
    return LIST_SUCCESS;
}

static ListStatus add_lists(const Node *first, const Node *second, Node **result)
{
    Node *head = NULL;
    Node *tail = NULL;

    if (result == NULL) {
        return LIST_INVALID_ARGUMENT;
    }

    *result = NULL;

    while (first != NULL || second != NULL) {
        int first_value = first != NULL ? first->value : 0;
        int second_value = second != NULL ? second->value : 0;
        int sum;
        ListStatus status;

        if ((second_value > 0 && first_value > INT_MAX - second_value) ||
            (second_value < 0 && first_value < INT_MIN - second_value)) {
            free_list(head);
            return LIST_ARITHMETIC_OVERFLOW;
        }

        sum = first_value + second_value;
        status = append_node(&head, &tail, sum);

        if (status != LIST_SUCCESS) {
            free_list(head);
            return status;
        }

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

static ListStatus print_list(const Node *head)
{
    if (printf("[") < 0) {
        return LIST_OUTPUT_FAILURE;
    }

    while (head != NULL) {
        if (printf("%d", head->value) < 0) {
            return LIST_OUTPUT_FAILURE;
        }

        if (head->next != NULL && printf(", ") < 0) {
            return LIST_OUTPUT_FAILURE;
        }

        head = head->next;
    }

    if (printf("]\n") < 0) {
        return LIST_OUTPUT_FAILURE;
    }

    return LIST_SUCCESS;
}

int main(void)
{
    const int first_values[] = {1, 2, 3, 4};
    const int second_values[] = {5, 6, 7};
    Node *first = NULL;
    Node *second = NULL;
    Node *sum = NULL;
    ListStatus status;
    int exit_code = EXIT_FAILURE;

    status = create_list(
        first_values,
        sizeof(first_values) / sizeof(first_values[0]),
        &first
    );
    if (status != LIST_SUCCESS) {
        goto cleanup;
    }

    status = create_list(
        second_values,
        sizeof(second_values) / sizeof(second_values[0]),
        &second
    );
    if (status != LIST_SUCCESS) {
        goto cleanup;
    }

    status = add_lists(first, second, &sum);
    if (status != LIST_SUCCESS) {
        goto cleanup;
    }

    status = print_list(sum);
    if (status != LIST_SUCCESS) {
        goto cleanup;
    }

    exit_code = EXIT_SUCCESS;

cleanup:
    free_list(sum);
    free_list(second);
    free_list(first);
    return exit_code;
}