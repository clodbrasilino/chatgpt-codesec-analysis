#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data)
{
    Node *node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

void print_list(const Node *head)
{
    while (head != NULL) {
        printf("%d", head->data);
        head = head->next;
        if (head != NULL) {
            printf(" -> ");
        }
    }
    printf("\n");
}

void free_list(Node *head)
{
    while (head != NULL) {
        Node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

Node *replace_last_with_list(Node *list, Node *replacement)
{
    if (list == NULL) {
        return replacement;
    }

    if (list->next == NULL) {
        free(list);
        return replacement;
    }

    Node *current = list;
    while (current->next->next != NULL) {
        current = current->next;
    }

    free(current->next);
    current->next = replacement;
    return list;
}

int main(void)
{
    Node *list = create_node(1);
    if (list == NULL) {
        return EXIT_FAILURE;
    }

    Node *second = create_node(2);
    if (second == NULL) {
        free_list(list);
        return EXIT_FAILURE;
    }
    list->next = second;

    Node *third = create_node(3);
    if (third == NULL) {
        free_list(list);
        return EXIT_FAILURE;
    }
    second->next = third;

    Node *replacement = create_node(4);
    if (replacement == NULL) {
        free_list(list);
        return EXIT_FAILURE;
    }

    Node *replacement_second = create_node(5);
    if (replacement_second == NULL) {
        free_list(list);
        free_list(replacement);
        return EXIT_FAILURE;
    }
    replacement->next = replacement_second;

    print_list(list);
    print_list(replacement);

    list = replace_last_with_list(list, replacement);

    print_list(list);

    free_list(list);
    return EXIT_SUCCESS;
}