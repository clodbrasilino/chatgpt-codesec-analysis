#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data) {
    Node *node = malloc(sizeof(*node));
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

void print_list(const Node *head) {
    const Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

Node *replace_last_with_list(Node *head, Node *replacement) {
    if (head == NULL) {
        return replacement;
    }

    Node **link = &head;
    while ((*link)->next != NULL) {
        link = &(*link)->next;
    }

    Node *last = *link;
    *link = replacement;
    free(last);

    return head;
}

int main(void) {
    Node *list = create_node(1);
    list->next = create_node(2);
    list->next->next = create_node(3);

    Node *replacement = create_node(4);
    replacement->next = create_node(5);

    list = replace_last_with_list(list, replacement);
    print_list(list);
    free_list(list);

    list = NULL;
    replacement = create_node(6);
    list = replace_last_with_list(list, replacement);
    print_list(list);
    free_list(list);

    list = create_node(7);
    list = replace_last_with_list(list, NULL);
    print_list(list);
    free_list(list);

    return 0;
}