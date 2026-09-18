#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *createNewNode(int data) {
    struct Node *newNode = malloc(sizeof(struct Node));

    if (newNode == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory for new node.\n");
        exit(1);
    }

    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

void swapFirstAndLast(struct Node **head) {
    if (*head == NULL) {
        fprintf(stderr, "Error: List is empty.\n");
        return;
    }

    struct Node *first = *head, *last = *head, *prev;

    while (last->next != NULL) {
        prev = last;
        last = last->next;
    }

    /* Possible weaknesses found:
     *  Access to field 'next' results in a dereference of an undefined pointer value (loaded from variable 'prev') [core.NullDereference]
     */
    prev->next = first;
    first->next = NULL;
    last->next = (*head)->next;
    *head = last;
}

void addToList(struct Node **head, int data) {
    struct Node *current = *head, *newNode = createNewNode(data);

    if (*head == NULL) {
        *head = newNode;
        return;
    } 

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode;
}

void printList(struct Node *head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }

    printf("NULL\n");
}

int main() {
    struct Node *head = NULL;

    for (int i = 1; i < 6; i++) {
        addToList(&head, i);
    }

    printf("Original list: ");
    printList(head);

    swapFirstAndLast(&head);

    printf("List after swapping first and last nodes: ");
    printList(head);

    return 0;
}