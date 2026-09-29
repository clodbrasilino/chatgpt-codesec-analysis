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

void append_node(Node **head, void *data, int is_list) {
    Node *new_node = create_node(data, is_list);
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

size_t count_and_square_lists(Node *head) {
    size_t count = 0;
    Node *current = head;
    while (current != NULL) {
        if (current->is_list) {
            count++;
        }
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    return count * count;
}

void free_inner_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

int main(void) {
    Node *inner_list1 = NULL;
    append_node(&inner_list1, (void *)1, 0);
    append_node(&inner_list1, (void *)2, 0);

    Node *inner_list2 = NULL;
    append_node(&inner_list2, (void *)3, 0);

    Node *outer_list = NULL;
    append_node(&outer_list, (void *)inner_list1, 1);
    append_node(&outer_list, (void *)inner_list2, 1);
    append_node(&outer_list, (void *)4, 0);

    size_t result = count_and_square_lists(outer_list);

    free_inner_list(inner_list1);
    free_inner_list(inner_list2);

    printf("%zu\n", result);

    return 0;
}