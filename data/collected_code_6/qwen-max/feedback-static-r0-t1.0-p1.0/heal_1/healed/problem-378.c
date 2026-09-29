#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node* create_node(int value) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

int is_empty(const Node *head) {
    return head == NULL;
}

void shift_last_to_first(Node **head) {
    if (is_empty(*head) || (*head)->next == NULL) {
        return;
    }

    Node *current = *head;
    Node *prev = NULL;

    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }

    if (prev != NULL) {
        prev->next = NULL;
    }
    current->next = *head;
    *head = current;
}

void print_list(const Node *head) {
    const Node *temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->value);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    Node *head = NULL;
    Node *second = NULL;
    Node *third = NULL;

    head = create_node(1);
    second = create_node(2);
    third = create_node(3);

    head->next = second;
    second->next = third;

    printf("Original list: ");
    print_list(head);

    shift_last_to_first(&head);

    printf("List after shifting last to first: ");
    print_list(head);

    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}