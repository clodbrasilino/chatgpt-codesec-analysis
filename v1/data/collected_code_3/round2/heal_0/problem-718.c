#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    new_node->data  = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

struct Node *createAlternateList(struct Node *head) {
    struct Node *result = NULL;
    struct Node **lastPtrRef = &result;
    int count = 0;

    while (head != NULL) {
        if (count % 2 == 0) {
            push(lastPtrRef, head->data);
            lastPtrRef = &((*lastPtrRef)->next);
        }
        head = head->next;
        count++;
    }
    return result;
}

void printList(struct Node *node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
}

int main() {
    struct Node* head = NULL;
    push(&head, 7);
    push(&head, 6);
    push(&head, 5);
    push(&head, 4);
    push(&head, 3);
    push(&head, 2);
    push(&head, 1);

    printf("Original list is: ");
    printList(head);

    struct Node* res = createAlternateList(head);
    printf("\nAlternate list is: ");
    printList(res);

    return 0;
}