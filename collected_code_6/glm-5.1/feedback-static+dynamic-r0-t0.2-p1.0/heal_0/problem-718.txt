#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

Node* alternate_list(Node* head) {
    if (head == NULL) {
        return NULL;
    }

    Node* new_head = create_node(head->data);
    Node* current_new = new_head;
    Node* current_old = head->next;

    int take = 0;
    while (current_old != NULL) {
        if (take) {
            current_new->next = create_node(current_old->data);
            current_new = current_new->next;
        }
        take = !take;
        current_old = current_old->next;
    }

    return new_head;
}

void free_list(Node* head) {
    Node* current = head;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    Node* head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);
    head->next->next->next = create_node(4);
    head->next->next->next->next = create_node(5);

    Node* alt_head = alternate_list(head);

    Node* current = alt_head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");

    free_list(head);
    free_list(alt_head);

    return 0;
}