#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_node(int data) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    if (new_node != NULL) {
        new_node->data = data;
        new_node->next = NULL;
    }
    return new_node;
}

void insert_end(Node** head, int data) {
    Node* new_node = create_node(data);
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

void delete_kth_element(Node** head, int k) {
    if (*head == NULL || k <= 0) {
        return;
    }

    if (k == 1) {
        Node* temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }

    Node* current = *head;
    for (int i = 1; current != NULL && i < k - 1; i++) {
        current = current->next;
    }

    if (current == NULL || current->next == NULL) {
        return;
    }

    Node* temp = current->next;
    current->next = current->next->next;
    free(temp);
}

void print_list(Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    Node* head = NULL;
    insert_end(&head, 10);
    insert_end(&head, 20);
    insert_end(&head, 30);
    insert_end(&head, 40);
    insert_end(&head, 50);

    printf("Original list: ");
    print_list(head);

    int k = 3;
    delete_kth_element(&head, k);

    printf("List after deleting %dth element: ", k);
    print_list(head);

    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}