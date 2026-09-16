#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int value;
    struct ListNode *next;
} ListNode;

typedef struct {
    int *items;
    size_t length;
} Tuple;

static void free_list(ListNode *head)
{
    while (head != NULL) {
        ListNode *next = head->next;
        free(head);
        head = next;
    }
}

static void free_tuple(Tuple *tuple)
{
    if (tuple != NULL) {
        free(tuple->items);
        tuple->items = NULL;
        tuple->length = 0;
    }
}

static int append_list_node(ListNode **head, ListNode **tail, int value)
{
    ListNode *node;

    if (head == NULL || tail == NULL) {
        return -1;
    }

    node = malloc(sizeof(*node));
    if (node == NULL) {
        return -1;
    }

    node->value = value;
    node->next = NULL;

    if (*tail == NULL) {
        *head = node;
    } else {
        (*tail)->next = node;
    }

    *tail = node;
    return 0;
}

static int list_to_tuple(const ListNode *head, Tuple *tuple)
{
    const ListNode *current;
    size_t count = 0;
    size_t index = 0;
    int *items;

    if (tuple == NULL) {
        return -1;
    }

    tuple->items = NULL;
    tuple->length = 0;

    for (current = head; current != NULL; current = current->next) {
        if (count == SIZE_MAX / sizeof(*items)) {
            return -1;
        }
        count++;
    }

    if (count == 0) {
        return 0;
    }

    items = malloc(count * sizeof(*items));
    if (items == NULL) {
        return -1;
    }

    for (current = head; current != NULL; current = current->next) {
        items[index++] = current->value;
    }

    tuple->items = items;
    tuple->length = count;
    return 0;
}

static int print_tuple(const Tuple *tuple)
{
    size_t i;

    if (tuple == NULL) {
        return -1;
    }

    if (putchar('(') == EOF) {
        return -1;
    }

    for (i = 0; i < tuple->length; i++) {
        if (i > 0 && printf(", ") < 0) {
            return -1;
        }
        if (printf("%d", tuple->items[i]) < 0) {
            return -1;
        }
    }

    if (tuple->length == 1 && putchar(',') == EOF) {
        return -1;
    }

    if (printf(")\n") < 0) {
        return -1;
    }

    return 0;
}

int main(void)
{
    const int values[] = {1, 2, 3, 4, 5};
    const size_t value_count = sizeof(values) / sizeof(values[0]);
    ListNode *head = NULL;
    ListNode *tail = NULL;
    Tuple tuple = {NULL, 0};
    size_t i;
    int status = EXIT_FAILURE;

    for (i = 0; i < value_count; i++) {
        if (append_list_node(&head, &tail, values[i]) != 0) {
            goto cleanup;
        }
    }

    if (list_to_tuple(head, &tuple) != 0) {
        goto cleanup;
    }

    if (print_tuple(&tuple) != 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free_tuple(&tuple);
    free_list(head);
    return status;
}