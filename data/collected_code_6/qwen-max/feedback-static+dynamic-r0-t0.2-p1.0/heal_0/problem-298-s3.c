#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node* createNode(int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void appendNode(Node **head, int value) {
    Node *newNode = createNode(value);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

int isPresent(Node *list, int value) {
    while (list != NULL) {
        if (list->value == value) {
            return 1;
        }
        list = list->next;
    }
    return 0;
}

void findNestedElements(Node *nestedList, Node *mainList) {
    while (nestedList != NULL) {
        if (isPresent(mainList, nestedList->value)) {
            printf("%d ", nestedList->value);
        }
        nestedList = nestedList->next;
    }
}

int main() {
    Node *mainList = NULL;
    Node *nestedList = NULL;

    appendNode(&mainList, 1);
    appendNode(&mainList, 2);
    appendNode(&mainList, 3);
    appendNode(&mainList, 4);

    appendNode(&nestedList, 2);
    appendNode(&nestedList, 4);
    appendNode(&nestedList, 5);

    findNestedElements(nestedList, mainList);

    Node *current;
    while (mainList != NULL) {
        current = mainList;
        mainList = mainList->next;
        free(current);
    }

    while (nestedList != NULL) {
        current = nestedList;
        nestedList = nestedList->next;
        free(current);
    }

    return 0;
}