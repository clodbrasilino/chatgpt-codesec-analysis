#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void insert_at_end(Node **head, int data) {
    Node *new_node = create_node(data);
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    Node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
}

void remove_kth_element(Node **head, int k) {
    if (k <= 0 || *head == NULL) {
        return;
    }
    if (k == 1) {
        Node *temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }
    Node *current = *head;
    for (int i = 1; current != NULL && i < k - 1; i++) {
        current = current->next;
    }
    if (current == NULL || current->next == NULL) {
        return;
    }
    Node *temp = current->next;
    current->next = current->next->next;
    free(temp);
}

void print_list(Node *head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    Node *head = NULL;
    insert_at_end(&head, 1);
    insert_at_end(&head, 2);
    insert_at_end(&head, 3);
    insert_at_end(&head, 4);
    insert_at_end(&head, 5);

    printf("Original list: ");
    print_list(head);

    remove_kth_element(&head, 3);

    printf("List after removing 3rd element: ");
    print_list(head);

    return 0;
}