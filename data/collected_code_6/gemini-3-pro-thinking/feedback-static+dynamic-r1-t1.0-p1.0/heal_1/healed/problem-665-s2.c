#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void shift_first_to_end(Node** head_ref);
void push(Node** head_ref, int new_data);
void print_list(Node* head);
void free_list(Node* head);

void shift_first_to_end(Node** head_ref) {
    if (head_ref == NULL || *head_ref == NULL || (*head_ref)->next == NULL) {
        return;
    }

    Node* first = *head_ref;
    Node* last = *head_ref;

    while (last->next != NULL) {
        last = last->next;
    }

    *head_ref = first->next;
    first->next = NULL;
    last->next = first;
}

void push(Node** head_ref, int new_data) {
    if (head_ref == NULL) {
        return;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }

    new_node->data = new_data;
    new_node->next = *head_ref;
    *head_ref = new_node;
}

void print_list(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void free_list(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void) {
    Node* head = NULL;

    push(&head, 5);
    push(&head, 4);
    push(&head, 3);
    push(&head, 2);
    push(&head, 1);

    print_list(head);
    shift_first_to_end(&head);
    print_list(head);

    free_list(head);
    head = NULL;

    return EXIT_SUCCESS;
}