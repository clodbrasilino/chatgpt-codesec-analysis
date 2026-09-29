#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node* create_node(int value) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void append_to_list(Node **head, int value) {
    Node *new_node = create_node(value);
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

void replace_last_with_list(Node **head, Node *new_list) {
    if (*head == NULL || new_list == NULL) {
        return;
    }
    Node *current = *head;
    while (current->next != NULL && current->next->next != NULL) {
        current = current->next;
    }
    current->next = new_list;
}

void print_list(Node *head) {
    while (head != NULL) {
        printf("%d -> ", head->value);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    Node *list1 = NULL;
    append_to_list(&list1, 1);
    append_to_list(&list1, 2);
    append_to_list(&list1, 3);

    Node *list2 = NULL;
    append_to_list(&list2, 4);
    append_to_list(&list2, 5);

    printf("List 1 before replacement: ");
    print_list(list1);

    printf("List 2: ");
    print_list(list2);

    replace_last_with_list(&list1, list2);

    printf("List 1 after replacement: ");
    print_list(list1);

    return 0;
}