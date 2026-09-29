#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void freeList(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}

int findMaxLengthSublist(Node *head, int *maxStart, int *maxEnd) {
    if (head == NULL) return 0;

    Node *current = head;
    int currentStart = 0, currentLen = 1, maxLen = 1, count = 0;

    while (current != NULL && current->next != NULL) {
        count++;
        if (current->data == current->next->data) {
            currentLen++;
        } else {
            if (currentLen > maxLen) {
                maxLen = currentLen;
                *maxStart = currentStart;
                *maxEnd = count - 1;
            }
            currentStart = count;
            currentLen = 1;
        }
        current = current->next;
    }

    if (currentLen > maxLen) {
        maxLen = currentLen;
        *maxStart = currentStart;
        *maxEnd = count;
    }

    return maxLen;
}

int main() {
    Node *head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(2);
    head->next->next->next = createNode(3);
    head->next->next->next->next = createNode(4);
    head->next->next->next->next->next = createNode(4);
    head->next->next->next->next->next->next = createNode(4);

    int maxLength, start, end;
    maxLength = findMaxLengthSublist(head, &start, &end);

    printf("Maximum Length: %d, Start: %d, End: %d\n", maxLength, start, end);

    freeList(head);
    return 0;
}