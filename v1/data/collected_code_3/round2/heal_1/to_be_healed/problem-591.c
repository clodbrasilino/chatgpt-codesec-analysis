#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

struct Node {
    int data;
    struct Node* next;
};

void swap(struct Node** head_ref) {
    struct Node* temp = *head_ref;
    struct Node* prev = NULL;

    if (temp == NULL || temp->next == NULL)
        return;

    while (temp->next != NULL) {
        prev = temp;
        temp = temp->next;
    }

    prev->next = *head_ref;
    temp->next = (*head_ref)->next;
    (*head_ref)->next = NULL;
    *head_ref = temp;
}

void push(struct Node** head_ref, int new_data) {
    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     */
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
        printf("%d  ", node->data);
        node = node->next;
    }
}

int main() {
    struct Node* start = NULL;

    push(&start, 12);
    push(&start, 56);
    push(&start, 2);
    push(&start, 11);

    printf("Linked list before calling swap function\n");
    printList(start);

    swap(&start);

    printf("\nLinked list after calling swap function\n");
    printList(start);

    return 0;
}