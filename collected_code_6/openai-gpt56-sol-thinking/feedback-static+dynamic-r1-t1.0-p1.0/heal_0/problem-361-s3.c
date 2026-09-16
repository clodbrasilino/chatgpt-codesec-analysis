#include <stdio.h>
#include <stdlib.h>

typedef struct IntNode {
    int value;
    struct IntNode *next;
} IntNode;

typedef struct ListNode {
    IntNode *head;
    struct ListNode *next;
} ListNode;

static ListNode *append_list(ListNode **lists)
{
    ListNode *new_list;
    ListNode **current;

    if (lists == NULL) {
        return NULL;
    }

    new_list = malloc(sizeof(*new_list));
    if (new_list == NULL) {
        return NULL;
    }

    new_list->head = NULL;
    new_list->next = NULL;

    current = lists;
    while (*current != NULL) {
        current = &(*current)->next;
    }
    *current = new_list;

    return new_list;
}

static int append_value(IntNode **head, int value)
{
    IntNode *new_node;
    IntNode **current;

    if (head == NULL) {
        return -1;
    }

    new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        return -1;
    }

    new_node->value = value;
    new_node->next = NULL;

    current = head;
    while (*current != NULL) {
        current = &(*current)->next;
    }
    *current = new_node;

    return 0;
}

static int remove_empty_lists(ListNode **lists)
{
    ListNode **current;

    if (lists == NULL) {
        return -1;
    }

    current = lists;

    while (*current != NULL) {
        ListNode *node = *current;

        if (node->head == NULL) {
            *current = node->next;
            free(node);
        } else {
            current = &node->next;
        }
    }

    return 0;
}

static void print_lists(const ListNode *lists)
{
    const ListNode *list = lists;

    while (list != NULL) {
        const IntNode *node = list->head;

        printf("[");
        while (node != NULL) {
            printf("%d", node->value);
            if (node->next != NULL) {
                printf(", ");
            }
            node = node->next;
        }
        printf("]\n");

        list = list->next;
    }
}

static void free_lists(ListNode **lists)
{
    ListNode *list;

    if (lists == NULL) {
        return;
    }

    list = *lists;
    while (list != NULL) {
        ListNode *next_list = list->next;
        IntNode *node = list->head;

        while (node != NULL) {
            IntNode *next_node = node->next;
            free(node);
            node = next_node;
        }

        free(list);
        list = next_list;
    }

    *lists = NULL;
}

int main(void)
{
    ListNode *lists = NULL;
    ListNode *list;

    if (append_list(&lists) == NULL) {
        free_lists(&lists);
        return EXIT_FAILURE;
    }

    list = append_list(&lists);
    if (list == NULL ||
        append_value(&list->head, 1) != 0 ||
        append_value(&list->head, 2) != 0) {
        free_lists(&lists);
        return EXIT_FAILURE;
    }

    if (append_list(&lists) == NULL) {
        free_lists(&lists);
        return EXIT_FAILURE;
    }

    list = append_list(&lists);
    if (list == NULL || append_value(&list->head, 3) != 0) {
        free_lists(&lists);
        return EXIT_FAILURE;
    }

    if (append_list(&lists) == NULL) {
        free_lists(&lists);
        return EXIT_FAILURE;
    }

    if (remove_empty_lists(&lists) != 0) {
        free_lists(&lists);
        return EXIT_FAILURE;
    }

    print_lists(lists);
    free_lists(&lists);

    return EXIT_SUCCESS;
}