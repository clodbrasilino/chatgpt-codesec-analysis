#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void appendNode(struct Node** head, int data) {
    if (head == NULL) {
        return;
    }
    
    struct Node* newNode = createNode(data);
    
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    
    struct Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

void swapFirstAndLast(struct Node** head) {
    if (head == NULL || *head == NULL || (*head)->next == NULL) {
        return;
    }

    struct Node* first = *head;
    struct Node* prev = NULL;
    struct Node* last = *head;

    while (last->next != NULL) {
        prev = last;
        last = last->next;
    }

    if (first->next == last) {
        last->next = first;
        first->next = NULL;
        *head = last;
    } else {
        last->next = first->next;
        prev->next = first;
        first->next = NULL;
        *head = last;
    }
}

void printList(const struct Node* head) {
    const struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void freeList(struct Node* head) {
    struct Node* current = head;
    struct Node* nextNode;
    
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
}

int main(void) {
    struct Node* head = NULL;

    appendNode(&head, 10);
    appendNode(&head, 20);
    appendNode(&head, 30);
    appendNode(&head, 40);
    appendNode(&head, 50);

    printList(head);
    swapFirstAndLast(&head);
    printList(head);

    freeList(head);
    head = NULL;

    return 0;
}