#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

Node* createNode(int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

List* createList() {
    List *list = (List *)malloc(sizeof(List));
    list->head = NULL;
    return list;
}

void addNodeToList(List *list, int value) {
    Node *newNode = createNode(value);
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

List* packConsecutiveDuplicates(List *inputList) {
    List *packedList = createList();
    Node *current = inputList->head;
    Node *previous = NULL;
    List *tempList = createList();

    while (current != NULL) {
        if (previous == NULL || previous->value != current->value) {
            if (tempList->head != NULL) {
                addNodeToList(packedList, tempList->head->value);
                Node *tempCurrent = tempList->head;
                while (tempCurrent != NULL) {
                    tempCurrent = tempCurrent->next;
                    free(tempList->head);
                    tempList->head = tempCurrent;
                }
                tempList->head = NULL;
            }
            addNodeToList(tempList, current->value);
        } else {
            addNodeToList(tempList, current->value);
        }
        previous = current;
        current = current->next;
    }

    if (tempList->head != NULL) {
        addNodeToList(packedList, tempList->head->value);
        Node *tempCurrent = tempList->head;
        while (tempCurrent != NULL) {
            tempCurrent = tempCurrent->next;
            free(tempList->head);
            tempList->head = tempCurrent;
        }
        tempList->head = NULL;
    }

    free(tempList);
    return packedList;
}

void printList(List *list) {
    Node *current = list->head;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

int main() {
    List *list = createList();
    addNodeToList(list, 1);
    addNodeToList(list, 1);
    addNodeToList(list, 2);
    addNodeToList(list, 3);
    addNodeToList(list, 3);
    addNodeToList(list, 3);
    addNodeToList(list, 4);

    printf("Original list: ");
    printList(list);

    List *packedList = packConsecutiveDuplicates(list);

    printf("Packed list: ");
    printList(packedList);

    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    free(list);

    current = packedList->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    free(packedList);

    return 0;
}