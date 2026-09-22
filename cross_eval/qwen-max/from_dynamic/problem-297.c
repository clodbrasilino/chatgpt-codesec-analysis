#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node* createNode(int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void appendToList(Node **head, int value) {
    Node *newNode = createNode(value);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

Node* flattenList(Node *head) {
    Node *flatList = NULL;
    Node *stack[100];
    int top = -1;
    stack[++top] = head;

    while (top >= 0) {
        Node *current = stack[top--];
        if (current == NULL) continue;
        appendToList(&flatList, current->value);
        if (current->next != NULL) {
            stack[++top] = current->next;
        }
    }

    return flatList;
}

void printList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

int main() {
    Node *head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);

    Node *nestedHead = createNode(10);
    nestedHead->next = createNode(20);
    nestedHead->next->next = head;

    Node *flattened = flattenList(nestedHead);
    printList(flattened);

    Node *current = flattened;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}