#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *createNode(int data) {
    Node *node = malloc(sizeof(*node));
    if (node != NULL) {
        node->data = data;
        node->next = NULL;
    }
    return node;
}

void freeList(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}

void printList(const Node *head) {
    while (head != NULL) {
        printf("%d", head->data);
        head = head->next;
        if (head != NULL) {
            printf(" -> ");
        }
    }
    printf("\n");
}

Node *rotateRight(Node *head, int k) {
    if (head == NULL || head->next == NULL || k <= 0) {
        return head;
    }

    Node *tail = head;
    int length = 1;

    while (tail->next != NULL) {
        tail = tail->next;
        length++;
    }

    k = k % length;
    if (k == 0) {
        return head;
    }

    int steps = length - k - 1;
    Node *newTail = head;

    for (int i = 0; i < steps; i++) {
        newTail = newTail->next;
    }

    Node *newHead = newTail->next;
    newTail->next = NULL;
    tail->next = head;

    return newHead;
}

int main(void) {
    int values[] = {1, 2, 3, 4, 5};
    size_t count = sizeof(values) / sizeof(values[0]);

    Node *head = NULL;
    Node *tail = NULL;

    for (size_t i = 0; i < count; i++) {
        Node *newNode = createNode(values[i]);
        if (newNode == NULL) {
            freeList(head);
            return EXIT_FAILURE;
        }

        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    printf("Original list:\n");
    printList(head);

    int k = 2;
    head = rotateRight(head, k);

    printf("Rotated list by %d to the right:\n", k);
    printList(head);

    freeList(head);
    return EXIT_SUCCESS;
}