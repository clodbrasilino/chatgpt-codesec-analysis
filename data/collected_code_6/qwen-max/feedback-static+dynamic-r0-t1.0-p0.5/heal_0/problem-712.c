#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

void addToList(List *list, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = list->head;
    list->head = newNode;
}

int isValueInList(List *list, int value) {
    Node *current = list->head;
    while (current != NULL) {
        if (current->value == value) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void removeDuplicates(List *lists, int numLists) {
    for (int i = 0; i < numLists; ++i) {
        List *currentList = &lists[i];
        List *uniqueList = (List *)malloc(sizeof(List));
        uniqueList->head = NULL;

        Node *current = currentList->head;
        while (current != NULL) {
            if (!isValueInList(uniqueList, current->value)) {
                addToList(uniqueList, current->value);
            }
            current = current->next;
        }

        currentList->head = uniqueList->head;
        free(uniqueList);
    }
}

void printList(List *list) {
    Node *current = list->head;
    while (current != NULL) {
        printf("%d -> ", current->value);
        current = current->next;
    }
    printf("NULL\n");
}

void freeList(List *list) {
    Node *current = list->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    List lists[3] = {{NULL}, {NULL}, {NULL}};
    addToList(&lists[0], 3);
    addToList(&lists[0], 2);
    addToList(&lists[0], 2);
    addToList(&lists[0], 1);

    addToList(&lists[1], 5);
    addToList(&lists[1], 4);
    addToList(&lists[1], 4);
    addToList(&lists[1], 3);

    addToList(&lists[2], 7);
    addToList(&lists[2], 6);
    addToList(&lists[2], 6);
    addToList(&lists[2], 5);

    printf("Before removing duplicates:\n");
    for (int i = 0; i < 3; ++i) {
        printList(&lists[i]);
    }

    removeDuplicates(lists, 3);

    printf("After removing duplicates:\n");
    for (int i = 0; i < 3; ++i) {
        printList(&lists[i]);
    }

    for (int i = 0; i < 3; ++i) {
        freeList(&lists[i]);
    }

    return 0;
}