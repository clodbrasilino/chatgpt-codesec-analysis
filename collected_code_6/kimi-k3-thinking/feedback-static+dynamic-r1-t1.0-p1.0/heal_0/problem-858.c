#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct IntNode {
    int data;
    struct IntNode *next;
} IntNode;

typedef struct ListNode {
    IntNode *items;
    struct ListNode *next;
} ListNode;

static IntNode *create_int_node(int data)
{
    IntNode *node = malloc(sizeof *node);
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

static ListNode *create_list_node(void)
{
    ListNode *node = malloc(sizeof *node);
    if (node == NULL) {
        return NULL;
    }
    node->items = NULL;
    node->next = NULL;
    return node;
}

static void free_int_list(IntNode *head)
{
    while (head != NULL) {
        IntNode *next = head->next;
        free(head);
        head = next;
    }
}

static void free_list_of_lists(ListNode *head)
{
    while (head != NULL) {
        ListNode *next = head->next;
        free_int_list(head->items);
        free(head);
        head = next;
    }
}

static int append_int(IntNode **head, IntNode **tail, int data)
{
    IntNode *node;
    if (head == NULL || tail == NULL) {
        return -1;
    }
    node = create_int_node(data);
    if (node == NULL) {
        return -1;
    }
    if (*tail != NULL) {
        (*tail)->next = node;
    } else {
        *head = node;
    }
    *tail = node;
    return 0;
}

static ListNode *build_sublist(const int *values, size_t length)
{
    ListNode *node;
    IntNode *tail = NULL;
    size_t i;

    if (values == NULL && length > 0) {
        return NULL;
    }
    node = create_list_node();
    if (node == NULL) {
        return NULL;
    }
    for (i = 0; i < length; i++) {
        if (append_int(&node->items, &tail, values[i]) != 0) {
            free_list_of_lists(node);
            return NULL;
        }
    }
    return node;
}

static int append_sublist(ListNode **head, ListNode **tail, const int *values, size_t length)
{
    ListNode *node;
    if (head == NULL || tail == NULL) {
        return -1;
    }
    node = build_sublist(values, length);
    if (node == NULL) {
        return -1;
    }
    if (*tail != NULL) {
        (*tail)->next = node;
    } else {
        *head = node;
    }
    *tail = node;
    return 0;
}

size_t count_lists(const ListNode *head)
{
    size_t count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

int squared_list_count(const ListNode *head, size_t *result)
{
    size_t count;
    if (result == NULL) {
        return -1;
    }
    count = count_lists(head);
    if (count != 0 && count > SIZE_MAX / count) {
        return -1;
    }
    *result = count * count;
    return 0;
}

int main(void)
{
    static const int first[]  = {1, 2, 3};
    static const int second[] = {4, 5};
    static const int third[]  = {6, 7, 8, 9};
    static const int fourth[] = {10};

    ListNode *head = NULL;
    ListNode *tail = NULL;
    size_t result = 0;
    int status = EXIT_SUCCESS;

    if (append_sublist(&head, &tail, first,  sizeof first  / sizeof first[0])  != 0 ||
        append_sublist(&head, &tail, second, sizeof second / sizeof second[0]) != 0 ||
        append_sublist(&head, &tail, third,  sizeof third  / sizeof third[0])  != 0 ||
        append_sublist(&head, &tail, fourth, sizeof fourth / sizeof fourth[0]) != 0) {
        fprintf(stderr, "Error: failed to build the list of lists\n");
        status = EXIT_FAILURE;
    } else if (squared_list_count(head, &result) != 0) {
        fprintf(stderr, "Error: failed to compute the squared count\n");
        status = EXIT_FAILURE;
    } else {
        printf("Number of lists: %zu\n", count_lists(head));
        printf("Squared count:   %zu\n", result);
    }

    free_list_of_lists(head);
    return status;
}