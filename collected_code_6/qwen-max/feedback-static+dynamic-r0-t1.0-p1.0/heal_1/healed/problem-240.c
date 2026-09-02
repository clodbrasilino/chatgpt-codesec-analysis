#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void append_to_list(Node **list, int data) {
    Node *new_node = create_node(data);
    if (*list == NULL) {
        *list = new_node;
    } else {
        Node *current = *list;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void replace_last_with_list(Node **main_list, Node *new_list) {
    if (*main_list == NULL || new_list == NULL) {
        return;
    }
    Node *current = *main_list;
    Node *previous = NULL;
    while (current->next != NULL) {
        previous = current;
        current = current->next;
    }
    if (previous == NULL) {
        *main_list = new_list;
    } else {
        previous->next = new_list;
    }
    free(current);
}

void print_list(Node *list) {
    while (list != NULL) {
        printf("%d -> ", list->data);
        list = list->next;
    }
    printf("NULL\n");
}

void free_list(Node *list) {
    Node *current = list;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    Node *main_list = NULL;
    Node *new_list = NULL;

    append_to_list(&main_list, 1);
    append_to_list(&main_list, 2);
    append_to_list(&main_list, 3);

    append_to_list(&new_list, 4);
    append_to_list(&new_list, 5);
    append_to_list(&new_list, 6);

    printf("Original List: ");
    print_list(main_list);

    printf("New List to Append: ");
    print_list(new_list);

    replace_last_with_list(&main_list, new_list);

    printf("Modified List: ");
    print_list(main_list);

    free_list(main_list);

    return 0;
}