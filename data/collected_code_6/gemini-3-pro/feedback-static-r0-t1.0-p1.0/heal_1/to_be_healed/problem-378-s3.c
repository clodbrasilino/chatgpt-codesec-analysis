#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void shiftLastToFirst(struct Node** head_ref) {
    if (head_ref == NULL || *head_ref == NULL || (*head_ref)->next == NULL) {
        return;
    }

    /* Possible weaknesses found:
     *  Assignment 'secLast=NULL', assigned value is 0
     */
    struct Node* secLast = NULL;
    struct Node* last = *head_ref;

    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    while (last->next != NULL) {
        secLast = last;
        last = last->next;
    }

    /* Possible weaknesses found:
     *  Possible null pointer dereference: secLast [nullPointer]
     *  Null pointer dereference
     */
    secLast->next = NULL;
    last->next = *head_ref;
    *head_ref = last;
}

void push(struct Node** head_ref, int new_data) {
    if (head_ref == NULL) {
        return;
    }
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
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

void freeList(struct Node* head) {
    /* Possible weaknesses found:
     *  The scope of the variable 'tmp' can be reduced. [variableScope]
     */
    struct Node* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
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

    shiftLastToFirst(&head);
    printList(head);

    freeList(head);

    return 0;
}