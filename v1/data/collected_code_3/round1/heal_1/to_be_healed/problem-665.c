#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void shiftFirstToEnd(struct Node** head_ref) {
    if (*head_ref == NULL || (*head_ref)->next == NULL)
        return;

    struct Node* first = *head_ref;
    struct Node* last = *head_ref;

    while (last->next != NULL)
        last = last->next;

    *head_ref = (*head_ref)->next;
    last->next = first;
    first->next = NULL;
}

void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'new_node' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
}

int main() {
    struct Node* head = NULL;

    push(&head, 5);
    push(&head, 4);
    push(&head, 3);
    push(&head, 2);
    push(&head, 1);

    printf("Original list: ");
    printList(head);

    shiftFirstToEnd(&head);

    printf("\nList after shifting first element to end: ");
    printList(head);

    return 0;
}