#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    struct List *down;
} List;

List* createNode(int value) {
    List *newNode = (List*)malloc(sizeof(List));
    newNode->head = (Node*)malloc(sizeof(Node));
    newNode->head->value = value;
    newNode->head->next = NULL;
    newNode->down = NULL;
    return newNode;
}

void append(List *list, int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;

    Node *current = list->head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

List* addRow(List *top, int value) {
    if (top == NULL) {
        return createNode(value);
    } else {
        top->down = addRow(top->down, value);
    }
    return top;
}

List* removeColumn(List *top, int column) {
    if (top == NULL) {
        return NULL;
    }

    List *current = top;
    while (current != NULL) {
        Node *prev = NULL;
        Node *node = current->head;
        int col = 0;
        while (node != NULL && col < column) {
            prev = node;
            node = node->next;
            col++;
        }
        if (node != NULL) {
            if (prev == NULL) {
                current->head = node->next;
            } else {
                prev->next = node->next;
            }
            free(node);
        }
        current = current->down;
    }
    return top;
}

void printList(List *top) {
    while (top != NULL) {
        Node *node = top->head;
        while (node != NULL) {
            printf("%d ", node->value);
            node = node->next;
        }
        printf("\n");
        top = top->down;
    }
}

int main() {
    List *top = NULL;
    top = addRow(top, 1);
    append(top, 2);
    append(top, 3);

    top = addRow(top, 4);
    append(top, 5);
    append(top, 6);

    top = addRow(top, 7);
    append(top, 8);
    append(top, 9);

    printf("Original list:\n");
    printList(top);

    top = removeColumn(top, 1);

    printf("List after removing column 1:\n");
    printList(top);

    return 0;
}