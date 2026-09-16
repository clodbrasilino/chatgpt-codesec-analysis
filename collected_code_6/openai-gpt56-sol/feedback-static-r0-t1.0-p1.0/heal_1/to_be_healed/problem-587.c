#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int value;
    struct ListNode *next;
} ListNode;

typedef struct {
    int *items;
    size_t size;
} Tuple;

static void free_list(ListNode *head)
{
    while (head != NULL) {
        ListNode *next = head->next;
        free(head);
        head = next;
    }
}

static int append_node(ListNode **head, ListNode **tail, int value)
{
    ListNode *node;

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

static int list_to_tuple(const ListNode *head, Tuple *tuple)
{
    const ListNode *current;
    size_t count = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'index' can be reduced. [variableScope]
     */
    size_t index = 0;
    int *items = NULL;

    if (tuple == NULL) {
        return 0;
    }

    tuple->items = NULL;
    tuple->size = 0;

    for (current = head; current != NULL; current = current->next) {
        if (count == SIZE_MAX / sizeof(*items)) {
            return 0;
        }
        ++count;
    }

    if (count != 0) {
        items = malloc(count * sizeof(*items));
        if (items == NULL) {
            return 0;
        }

        for (current = head; current != NULL; current = current->next) {
            items[index++] = current->value;
        }
    }

    tuple->items = items;
    tuple->size = count;
    return 1;
}

static void free_tuple(Tuple *tuple)
{
    if (tuple != NULL) {
        free(tuple->items);
        tuple->items = NULL;
        tuple->size = 0;
    }
}

static int print_tuple(const Tuple *tuple)
{
    size_t i;

    if (tuple == NULL) {
        return 0;
    }

    if (putchar('(') == EOF) {
        return 0;
    }

    for (i = 0; i < tuple->size; ++i) {
        if (i != 0 && printf(", ") < 0) {
            return 0;
        }
        if (printf("%d", tuple->items[i]) < 0) {
            return 0;
        }
    }

    if (tuple->size == 1 && putchar(',') == EOF) {
        return 0;
    }

    if (printf(")\n") < 0) {
        return 0;
    }

    return 1;
}

int main(void)
{
    ListNode *head = NULL;
    ListNode *tail = NULL;
    Tuple tuple = {NULL, 0};
    const int values[] = {1, 2, 3, 4, 5};
    const size_t value_count = sizeof(values) / sizeof(values[0]);
    size_t i;
    int status = EXIT_FAILURE;

    for (i = 0; i < value_count; ++i) {
        if (!append_node(&head, &tail, values[i])) {
            goto cleanup;
        }
    }

    if (!list_to_tuple(head, &tuple)) {
        goto cleanup;
    }

    if (!print_tuple(&tuple)) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free_tuple(&tuple);
    free_list(head);
    return status;
}