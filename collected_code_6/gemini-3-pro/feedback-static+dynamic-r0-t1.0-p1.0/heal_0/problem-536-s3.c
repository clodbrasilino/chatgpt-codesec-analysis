#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void appendNode(Node** head, int data) {
    if (!head) {
        return;
    }
    Node* newNode = createNode(data);
    if (!newNode) {
        return;
    }
    if (!*head) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
}

Node* getNthNode(Node* head, unsigned int n) {
    Node* current = head;
    unsigned int count = 0;
    while (current != NULL) {
        if (count == n) {
            return current;
        }
        count++;
        current = current->next;
    }
    return NULL;
}

void freeList(Node* head) {
    Node* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main(void) {
    Node* head = NULL;
    
    appendNode(&head, 10);
    appendNode(&head, 20);
    appendNode(&head, 30);
    appendNode(&head, 40);
    appendNode(&head, 50);

    Node* target = getNthNode(head, 2);
    if (target) {
        printf("%d\n", target->data);
    } else {
        printf("Out of bounds\n");
    }

    target = getNthNode(head, 10);
    if (target) {
        printf("%d\n", target->data);
    } else {
        printf("Out of bounds\n");
    }

    freeList(head);
    return 0;
}