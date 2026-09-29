#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

static Node *create_node(int data)
{
    Node *node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

static void free_list(Node *head)
{
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

static int list_contains_sublist(const Node *list, const Node *sublist)
{
    if (sublist == NULL) {
        return 1;
    }

    for (const Node *current = list; current != NULL; current = current->next) {
        const Node *list_iter = current;
        const Node *sub_iter = sublist;

        while (list_iter != NULL && sub_iter != NULL && list_iter->data == sub_iter->data) {
            list_iter = list_iter->next;
            sub_iter = sub_iter->next;
        }

        if (sub_iter == NULL) {
            return 1;
        }
    }

    return 0;
}

int main(void)
{
    int list_values[] = {1, 2, 3, 4, 5, 6};
    int sublist_values[] = {3, 4, 5};
    size_t list_size = sizeof(list_values) / sizeof(list_values[0]);
    size_t sublist_size = sizeof(sublist_values) / sizeof(sublist_values[0]);
    Node *list_head = NULL;
    Node *sublist_head = NULL;
    Node *tail = NULL;

    for (size_t i = 0; i < list_size; ++i) {
        Node *node = create_node(list_values[i]);
        if (node == NULL) {
            free_list(list_head);
            free_list(sublist_head);
            return EXIT_FAILURE;
        }
        if (list_head == NULL) {
            list_head = node;
        } else {
            tail->next = node;
        }
        tail = node;
    }

    tail = NULL;
    for (size_t i = 0; i < sublist_size; ++i) {
        Node *node = create_node(sublist_values[i]);
        if (node == NULL) {
            free_list(list_head);
            free_list(sublist_head);
            return EXIT_FAILURE;
        }
        if (sublist_head == NULL) {
            sublist_head = node;
        } else {
            tail->next = node;
        }
        tail = node;
    }

    printf("%s\n", list_contains_sublist(list_head, sublist_head) ? "true" : "false");

    free_list(list_head);
    free_list(sublist_head);

    return EXIT_SUCCESS;
}