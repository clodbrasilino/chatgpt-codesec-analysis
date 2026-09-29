#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void splitList(struct Node* head, int n, struct Node** first, struct Node** second) {
    struct Node* current = head;
    int count = 1;

    if (head == NULL) {
        return;
    }

    while (count < n && current != NULL) {
        current = current->next;
        count++;
    }

    if (current == NULL) {
        return;
    }

    *first = head;
    *second = current->next;
    current->next = NULL;
}

void push(struct Node** head, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'new_node' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    new_node->data = new_data;
    new_node->next = (*head);
    (*head) = new_node;
}

void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
}

int main() {
    struct Node* head = NULL;
    struct Node* first = NULL;
    struct Node* second = NULL;

    push(&head, 1);
    push(&head, 2);
    push(&head, 3);
    push(&head, 4);
    push(&head, 5);

    printf("Original list: ");
    printList(head);

    splitList(head, 3, &first, &second);

    printf("\nFirst part of list: ");
    printList(first);

    printf("\nSecond part of list: ");
    printList(second);

    return 0;
}