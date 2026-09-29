#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void appendNode(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void freeList(struct Node* head) {
    while (head != NULL) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
    }
}

struct Node* rotateLeft(struct Node* head, int k) {
    if (head == NULL || head->next == NULL || k == 0) {
        return head;
    }

    struct Node* current = head;
    int count = 1;

    while (count < k && current != NULL) {
        current = current->next;
        count++;
    }

    if (current == NULL) {
        return head;
    }

    struct Node* kthNode = current;

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = head;
    head = kthNode->next;
    kthNode->next = NULL;

    return head;
}

int main(void) {
    struct Node* head = NULL;

    appendNode(&head, 10);
    appendNode(&head, 20);
    appendNode(&head, 30);
    appendNode(&head, 40);
    appendNode(&head, 50);
    appendNode(&head, 60);

    head = rotateLeft(head, 4);

    printList(head);

    freeList(head);

    return 0;
}