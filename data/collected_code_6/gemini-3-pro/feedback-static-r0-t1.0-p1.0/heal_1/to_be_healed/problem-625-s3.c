#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void swapFirstAndLast(struct Node** head_ref) {
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

    last->next = (*head_ref)->next;
    /* Possible weaknesses found:
     *  Possible null pointer dereference: secLast [nullPointer]
     *  Null pointer dereference
     */
    secLast->next = *head_ref;
    (*head_ref)->next = NULL;
    *head_ref = last;
}

void push(struct Node** head_ref, int new_data) {
    if (head_ref == NULL) {
        return;
    }
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
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
    struct Node* start = NULL;

    push(&start, 5);
    push(&start, 4);
    push(&start, 3);
    push(&start, 2);
    push(&start, 1);

    swapFirstAndLast(&start);

    printList(start);

    freeList(start);

    return 0;
}