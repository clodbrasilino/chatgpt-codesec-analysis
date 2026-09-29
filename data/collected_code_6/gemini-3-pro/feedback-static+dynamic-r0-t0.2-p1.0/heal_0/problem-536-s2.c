#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void appendNode(Node** head, int data) {
    if (!head) return;
    Node* newNode = createNode(data);
    if (!*head) {
        *head = newNode;
        return;
    }
    Node* current = *head;
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
}

void freeList(Node* head) {
    Node* current = head;
    while (current) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

Node* getNthItems(Node* head, int n) {
    if (!head || n <= 0) {
        return NULL;
    }

    Node* resultHead = NULL;
    Node* current = head;
    int count = 1;

    while (current) {
        if (count % n == 0) {
            appendNode(&resultHead, current->data);
        }
        current = current->next;
        count++;
    }

    return resultHead;
}

void printList(Node* head) {
    Node* current = head;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    Node* head = NULL;

    for (int i = 1; i <= 10; i++) {
        appendNode(&head, i);
    }

    Node* nthItems = getNthItems(head, 3);

    if (nthItems) {
        printList(nthItems);
    }

    freeList(head);
    freeList(nthItems);

    return EXIT_SUCCESS;
}