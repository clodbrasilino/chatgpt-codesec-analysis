#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    void *data;
    int is_list;
    struct Node *next;
} Node;

Node *create_node(void *data, int is_list) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->is_list = is_list;
    node->next = NULL;
    return node;
}

void append_node(Node *head, Node *new_node) {
    if (head == NULL || new_node == NULL) {
        return;
    }
    Node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

size_t count_and_square_lists(Node *head) {
    size_t count = 0;
    Node *current = head;
    while (current != NULL) {
        if (current->is_list) {
            count++;
        }
        current = current->next;
    }
    return count * count;
}

void free_list(Node *head, int free_sublists) {
    Node *current = head;
    while (current != NULL) {
        if (current->is_list && free_sublists) {
            free_list((Node *)current->data, 1);
        }
        Node *next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    Node *sublist1 = create_node((void *)(long)100, 0);
    append_node(sublist1, create_node((void *)(long)200, 0));

    Node *sublist2 = create_node((void *)(long)300, 0);

    Node *head = create_node((void *)sublist1, 1);
    append_node(head, create_node((void *)(long)400, 0));
    append_node(head, create_node((void *)sublist2, 1));
    append_node(head, create_node((void *)(long)500, 0));
    append_node(head, create_node((void *)NULL, 1));

    size_t result = count_and_square_lists(head);
    printf("%zu\n", result);

    free_list(head, 1);

    return 0;
}