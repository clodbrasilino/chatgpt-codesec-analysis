#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LIST_NODES 1024U

typedef struct Node {
    int64_t value;
    struct Node *next;
} Node;

typedef enum {
    SUM_SUCCESS,
    SUM_INVALID_ARGUMENT,
    SUM_CYCLE_DETECTED,
    SUM_LIST_TOO_LONG,
    SUM_OVERFLOW
} SumStatus;

static void free_list(Node *head)
{
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

static SumStatus sum_nodes_recursive(const Node *node, size_t remaining,
                                     int64_t *result)
{
    int64_t tail_sum;
    SumStatus status;

    if (remaining == 0U) {
        *result = 0;
        return node == NULL ? SUM_SUCCESS : SUM_INVALID_ARGUMENT;
    }

    if (node == NULL) {
        return SUM_INVALID_ARGUMENT;
    }

    status = sum_nodes_recursive(node->next, remaining - 1U, &tail_sum);
    if (status != SUM_SUCCESS) {
        return status;
    }

    if ((node->value > 0 && tail_sum > INT64_MAX - node->value) ||
        (node->value < 0 && tail_sum < INT64_MIN - node->value)) {
        return SUM_OVERFLOW;
    }

    *result = node->value + tail_sum;
    return SUM_SUCCESS;
}

SumStatus recursive_list_sum(const Node *head, int64_t *result)
{
    const Node *slow = head;
    const Node *fast = head;
    const Node *current;
    size_t count = 0U;

    if (result == NULL) {
        return SUM_INVALID_ARGUMENT;
    }

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return SUM_CYCLE_DETECTED;
        }
    }

    for (current = head; current != NULL; current = current->next) {
        if (count == MAX_LIST_NODES) {
            return SUM_LIST_TOO_LONG;
        }
        ++count;
    }

    return sum_nodes_recursive(head, count, result);
}

static int append_node(Node **head, Node **tail, int64_t value)
{
    Node *node;

    if (head == NULL || tail == NULL) {
        return 0;
    }

    node = malloc(sizeof(*node));
    if (node == NULL) {
        return 0;
    }

    node->value = value;
    node->next = NULL;

    if (*tail == NULL) {
        *head = node;
    } else {
        (*tail)->next = node;
    }

    *tail = node;
    return 1;
}

int main(void)
{
    const int64_t values[] = {10, 20, 30, 40, 50};
    const size_t value_count = sizeof(values) / sizeof(values[0]);
    Node *head = NULL;
    Node *tail = NULL;
    int64_t sum;
    SumStatus status;
    size_t i;

    for (i = 0U; i < value_count; ++i) {
        if (!append_node(&head, &tail, values[i])) {
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    status = recursive_list_sum(head, &sum);
    if (status != SUM_SUCCESS) {
        free_list(head);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", sum) < 0) {
        free_list(head);
        return EXIT_FAILURE;
    }

    free_list(head);
    return EXIT_SUCCESS;
}