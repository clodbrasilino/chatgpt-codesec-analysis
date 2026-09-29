#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int value;
    struct ListNode *next;
} ListNode;

typedef struct {
    int *values;
    size_t size;
} Tuple;

static ListNode *list_node_create(int value)
{
    ListNode *node = malloc(sizeof(*node));

    if (node == NULL) {
        return NULL;
    }

    node->value = value;
    node->next = NULL;
    return node;
}

static int list_append(ListNode **head, ListNode **tail, int value)
{
    ListNode *node;

    if (head == NULL || tail == NULL) {
        return -1;
    }

    node = list_node_create(value);
    if (node == NULL) {
        return -1;
    }

    if (*tail == NULL) {
        *head = node;
    } else {
        (*tail)->next = node;
    }

    *tail = node;
    return 0;
}

static void list_destroy(ListNode **head)
{
    ListNode *current;

    if (head == NULL) {
        return;
    }

    current = *head;
    while (current != NULL) {
        ListNode *next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}

static int list_to_tuple(const ListNode *head, Tuple *tuple)
{
    const ListNode *current;
    size_t count = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'index' can be reduced. [variableScope]
     */
    size_t index = 0;
    int *values = NULL;

    if (tuple == NULL) {
        return -1;
    }

    tuple->values = NULL;
    tuple->size = 0;

    for (current = head; current != NULL; current = current->next) {
        if (count == SIZE_MAX / sizeof(*values)) {
            return -1;
        }
        ++count;
    }

    if (count != 0) {
        values = malloc(count * sizeof(*values));
        if (values == NULL) {
            return -1;
        }

        for (current = head; current != NULL; current = current->next) {
            values[index++] = current->value;
        }
    }

    tuple->values = values;
    tuple->size = count;
    return 0;
}

static void tuple_destroy(Tuple *tuple)
{
    if (tuple == NULL) {
        return;
    }

    free(tuple->values);
    tuple->values = NULL;
    tuple->size = 0;
}

static int tuple_print(const Tuple *tuple)
{
    size_t i;

    if (tuple == NULL || (tuple->size != 0 && tuple->values == NULL)) {
        return -1;
    }

    if (putchar('(') == EOF) {
        return -1;
    }

    for (i = 0; i < tuple->size; ++i) {
        if (i != 0 && printf(", ") < 0) {
            return -1;
        }

        if (printf("%d", tuple->values[i]) < 0) {
            return -1;
        }
    }

    if (tuple->size == 1 && putchar(',') == EOF) {
        return -1;
    }

    if (printf(")\n") < 0) {
        return -1;
    }

    return 0;
}

int main(void)
{
    const int input[] = {1, 2, 3, 4, 5};
    const size_t input_count = sizeof(input) / sizeof(input[0]);
    ListNode *head = NULL;
    ListNode *tail = NULL;
    Tuple tuple = {NULL, 0};
    size_t i;
    int status = EXIT_FAILURE;

    for (i = 0; i < input_count; ++i) {
        if (list_append(&head, &tail, input[i]) != 0) {
            fprintf(stderr, "Failed to build list.\n");
            goto cleanup;
        }
    }

    if (list_to_tuple(head, &tuple) != 0) {
        fprintf(stderr, "Failed to convert list to tuple.\n");
        goto cleanup;
    }

    if (tuple_print(&tuple) != 0) {
        fprintf(stderr, "Failed to print tuple.\n");
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    tuple_destroy(&tuple);
    list_destroy(&head);
    return status;
}