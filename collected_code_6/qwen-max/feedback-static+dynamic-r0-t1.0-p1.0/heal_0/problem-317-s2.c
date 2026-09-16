#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    int count;
    struct Node *next;
} Node;

Node* createNode(int value, int count) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = value;
    newNode->count = count;
    newNode->next = NULL;
    return newNode;
}

void addNode(Node **head, int value, int count) {
    if (*head == NULL) {
        *head = createNode(value, count);
    } else {
        Node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = createNode(value, count);
    }
}

Node* decode(Node *encodedList) {
    Node *decodedList = NULL;
    while (encodedList != NULL) {
        for (int i = 0; i < encodedList->count; ++i) {
            addNode(&decodedList, encodedList->value, 1);
        }
        encodedList = encodedList->next;
    }
    return decodedList;
}

void printList(Node *head) {
    while (head != NULL) {
        for (int i = 0; i < head->count; ++i) {
            printf("%d ", head->value);
        }
        head = head->next;
    }
    printf("\n");
}

void freeList(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node *encodedList = NULL;
    
    addNode(&encodedList, 2, 3);
    addNode(&encodedList, 3, 5);
    addNode(&encodedList, 1, 2);

    printf("Encoded List: ");
    printList(encodedList);

    Node *decodedList = decode(encodedList);

    printf("Decoded List: ");
    printList(decodedList);

    freeList(encodedList);
    freeList(decodedList);

    return 0;
}