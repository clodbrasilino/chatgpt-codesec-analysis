#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *createNode(int data) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

void append(struct Node **head, int data) {
    struct Node *newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

struct Node *rotateLeft(struct Node *head, int k) {
    if (head == NULL || k <= 0) {
        return head;
    }

    struct Node *tail = head;
    int length = 1;
    while (tail->next != NULL) {
        tail = tail->next;
        length++;
    }

    k %= length;
    if (k == 0) {
        return head;
    }

    struct Node *current = head;
    int i;
    for (i = 0; i < k - 1; i++) {
        current = current->next;
    }

    struct Node *newHead = current->next;
    current->next = NULL;
    tail->next = head;
    return newHead;
}

void printList(struct Node *head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void freeList(struct Node *head) {
    while (head != NULL) {
        struct Node *temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void) {
    struct Node *head = NULL;
    append(&head, 1);
    append(&head, 2);
    append(&head, 3);
    append(&head, 4);
    append(&head, 5);

    printf("Original list: ");
    printList(head);

    head = rotateLeft(head, 2);

    printf("Rotated list: ");
    printList(head);

    freeList(head);
    return 0;
}