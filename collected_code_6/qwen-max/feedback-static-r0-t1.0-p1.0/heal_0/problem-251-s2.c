#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* create_node(int data) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(1);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void insert_before_each(Node **head, int value) {
    if (*head == NULL) {
        return;
    }

    Node *current = *head;
    *head = create_node(value);
    (*head)->next = current;

    while (current != NULL && current->next != NULL) {
        Node *temp = current->next;
        current->next = create_node(value);
        current->next->next = temp;
        current = temp;
    }
}

void print_list(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void free_list(Node *head) {
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node *head = NULL;
    head = create_node(10);
    head->next = create_node(20);
    head->next->next = create_node(30);

    printf("Original List: ");
    print_list(head);

    insert_before_each(&head, 5);

    printf("List after insertion: ");
    print_list(head);

    free_list(head);
    return 0;
}