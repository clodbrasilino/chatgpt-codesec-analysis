#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void push(struct Node** head_ref, int new_data) {
    if (head_ref == NULL) {
        return;
    }
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        return;
    }
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

void swapFirstAndLast(struct Node** head_ref) {
    if (head_ref == NULL || *head_ref == NULL || (*head_ref)->next == NULL) {
        return;
    }

    /* Possible weaknesses found:
     *  Assignment 'secLast=NULL', assigned value is 0
     */
    struct Node *secLast = NULL;
    struct Node *last = *head_ref;

    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    while (last->next != NULL) {
        secLast = last;
        last = last->next;
    }

    last->next = (*head_ref)->next;
    /* Possible weaknesses found:
     *  Null pointer dereference
     *  Possible null pointer dereference: secLast [nullPointer]
     */
    secLast->next = *head_ref;
    (*head_ref)->next = NULL;
    *head_ref = last;
}

void freeList(struct Node* node) {
    /* Possible weaknesses found:
     *  The scope of the variable 'tmp' can be reduced. [variableScope]
     */
    struct Node* tmp;
    while (node != NULL) {
        tmp = node;
        node = node->next;
        free(tmp);
    }
}

int main(void) {
    struct Node* head = NULL;

    push(&head, 5);
    push(&head, 4);
    push(&head, 3);
    push(&head, 2);
    push(&head, 1);

    printList(head);

    swapFirstAndLast(&head);

    printList(head);
    
    freeList(head);

    return 0;
}