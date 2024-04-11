#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        return;
    }
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void printList(struct Node *node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
}

void extractSingle(struct Node **head_ref) {
    struct Node* current = *head_ref;
    struct Node* prev = NULL;
    struct Node* next;

    while (current != NULL) {
        next = current->next;
        if(next != NULL && current->data != next->data && (prev == NULL || prev->data != current->data)){
            printf("%d ", current->data);
        }
        prev = current;
        current = next;
    }
}

int main() {
    struct Node* head = NULL;

    push(&head, 5);
    push(&head, 5);
    push(&head, 4);
    push(&head, 3);
    push(&head, 3);
    push(&head, 2);
    push(&head, 1);
    push(&head, 1);
    push(&head, 1);

    printf("Created Linked List: ");
    printList(head);

    printf("\nExtracted elements: ");
    extractSingle(&head);

    return 0;
}