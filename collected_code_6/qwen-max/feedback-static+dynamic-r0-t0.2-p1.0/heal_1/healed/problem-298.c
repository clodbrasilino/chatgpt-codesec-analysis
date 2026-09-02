#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

Node* create_node(int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->value = value;
    new_node->next = NULL;
    return new_new_node;
}

void append(List *list, int value) {
    Node *new_node = create_node(value);
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

int is_present(const Node *node, const List *list) {
    Node *current = list->head;
    while (current != NULL) {
        if (current->value == node->value) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void find_nested_elements(const List *nested_list, const List *main_list) {
    Node *current = nested_list->head;
    while (current != NULL) {
        if (is_present(current, main_list)) {
            printf("%d\n", current->value);
        }
        current = current->next;
    }
}

int main() {
    List nested_list = {NULL};
    List main_list = {NULL};

    append(&nested_list, 1);
    append(&nested_list, 2);
    append(&nested_list, 3);

    append(&main_list, 2);
    append(&main_list, 3);
    append(&main_list, 4);

    find_nested_elements(&nested_list, &main_list);

    return 0;
}