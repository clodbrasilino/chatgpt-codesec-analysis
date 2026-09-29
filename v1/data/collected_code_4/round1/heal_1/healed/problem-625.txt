#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node* createNewNode(int data) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory for new node.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void swapFirstAndLast(struct Node **head) {
    if (*head == NULL || (*head)->next == NULL) {
        fprintf(stderr, "Error: List is empty or only has one node.\n");
        return;
    } 

    struct Node *prev = NULL;
    struct Node *first = *head;
    struct Node *last = *head;

    while (last->next != NULL) {
        prev = last;
        last = last->next;
    }

    prev->next = first;
    first->next = last->next;
    last->next = *head;
    *head = last;
}

void addToList(struct Node **head, int data) {
    struct Node *newNode = createNewNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void printList(struct Node *head) {
    struct Node *temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node *head = NULL;

    for (int i = 1; i <= 5; i++) {
        addToList(&head, i);
    }

    printf("Original list: ");
    printList(head);

    swapFirstAndLast(&head);

    printf("List after swapping first and last nodes: ");
    printList(head);

    return 0;
}