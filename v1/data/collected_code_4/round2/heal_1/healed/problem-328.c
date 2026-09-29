#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void push(struct Node** head_ref, int data) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    if(newNode == NULL) {
        return;
    }

    newNode->data = data;
    newNode->next = (*head_ref);
    (*head_ref) = newNode;
}

void rotate(struct Node** head_ref, int k) {
    if (k == 0) { return; }

    struct Node* current = *head_ref;
    int count = 1;

    while (count < k && current != NULL) {
        current = current->next;
        count++;
    }
    
    if (current == NULL) { return; }

    struct Node* kthNode = current;

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = *head_ref;
    *head_ref = kthNode->next;
    kthNode->next = NULL;
}

void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
}

int main(void) {
    struct Node* head = NULL;

    push(&head, 7);
    push(&head, 6);
    push(&head, 5);
    push(&head, 4);
    push(&head, 3);
    push(&head, 2);
    push(&head, 1);

    printf("Given list: ");
    printList(head);

    rotate(&head, 4);

    printf("\nRotated list: ");
    printList(head);

    return 0;
}