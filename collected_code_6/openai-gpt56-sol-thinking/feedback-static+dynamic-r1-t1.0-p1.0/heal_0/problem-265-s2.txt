#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int value;
    struct ListNode *next;
} ListNode;

typedef enum {
    SPLIT_OK = 0,
    SPLIT_INVALID_ARGUMENT,
    SPLIT_CYCLIC_LIST,
    SPLIT_ALLOCATION_FAILURE
} SplitStatus;

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

static int has_cycle(const ListNode *head)
{
    const ListNode *slow = head;
    const ListNode *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return 1;
        }
    }

    return 0;
}

static SplitStatus split_every_n(ListNode *head, size_t n,
                                 ListNode ***out_lists,
                                 size_t *out_count)
{
    ListNode **lists;
    ListNode *current;
    size_t length = 0;
    size_t list_count;
    size_t index = 0;

    if (out_lists == NULL || out_count == NULL || n == 0) {
        return SPLIT_INVALID_ARGUMENT;
    }

    *out_lists = NULL;
    *out_count = 0;

    if (head == NULL) {
        return SPLIT_OK;
    }

    if (has_cycle(head)) {
        return SPLIT_CYCLIC_LIST;
    }

    for (current = head; current != NULL; current = current->next) {
        if (length == SIZE_MAX) {
            return SPLIT_ALLOCATION_FAILURE;
        }
        ++length;
    }

    list_count = length / n;
    if (length % n != 0) {
        ++list_count;
    }

    if (list_count > SIZE_MAX / sizeof(*lists)) {
        return SPLIT_ALLOCATION_FAILURE;
    }

    lists = calloc(list_count, sizeof(*lists));
    if (lists == NULL) {
        return SPLIT_ALLOCATION_FAILURE;
    }

    current = head;

    while (current != NULL) {
        ListNode *last = current;
        ListNode *next;
        size_t position;

        lists[index++] = current;

        for (position = 1; position < n && last->next != NULL; ++position) {
            last = last->next;
        }

        next = last->next;
        last->next = NULL;
        current = next;
    }

    *out_lists = lists;
    *out_count = list_count;
    return SPLIT_OK;
}

static void print_list(const ListNode *head)
{
    const ListNode *current = head;

    while (current != NULL) {
        printf("%d", current->value);
        current = current->next;

        if (current != NULL) {
            printf(" ");
        }
    }

    putchar('\n');
}

int main(void)
{
    const int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    const size_t value_count = sizeof(values) / sizeof(values[0]);
    const size_t n = 3;
    ListNode *head = NULL;
    ListNode *tail = NULL;
    ListNode **lists = NULL;
    size_t list_count = 0;
    size_t i;
    SplitStatus status;

    for (i = 0; i < value_count; ++i) {
        if (!append_node(&head, &tail, values[i])) {
            fprintf(stderr, "Failed to create list\n");
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    status = split_every_n(head, n, &lists, &list_count);
    if (status != SPLIT_OK) {
        fprintf(stderr, "Failed to split list: status %d\n", (int)status);
        free_list(head);
        return EXIT_FAILURE;
    }

    for (i = 0; i < list_count; ++i) {
        print_list(lists[i]);
    }

    for (i = 0; i < list_count; ++i) {
        free_list(lists[i]);
    }

    free(lists);
    return EXIT_SUCCESS;
}