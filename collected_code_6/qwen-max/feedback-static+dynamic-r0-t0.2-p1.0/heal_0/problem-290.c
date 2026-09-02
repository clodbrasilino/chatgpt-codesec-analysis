#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    int length;
} List;

void addNode(List *list, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    list->length++;
}

List* createList() {
    List *list = (List *)malloc(sizeof(List));
    list->head = NULL;
    list->length = 0;
    return list;
}

void freeList(List *list) {
    Node *current = list->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

List* findMaxLengthList(List **lists, int numLists) {
    if (numLists == 0) return NULL;

    List *maxList = lists[0];
    for (int i = 1; i < numLists; i++) {
        if (lists[i]->length > maxList->length) {
            maxList = lists[i];
        }
    }
    return maxList;
}

int main() {
    int numLists = 3;
    List *lists[3];

    for (int i = 0; i < numLists; i++) {
        lists[i] = createList();
    }

    addNode(lists[0], 1);
    addNode(lists[0], 2);

    addNode(lists[1], 1);
    addNode(lists[1], 2);
    addNode(lists[1], 3);

    addNode(lists[2], 1);

    List *maxList = findMaxLengthList(lists, numLists);

    if (maxList != NULL) {
        printf("Max Length List: %d\n", maxList->length);
    } else {
        printf("No lists found.\n");
    }

    for (int i = 0; i < numLists; i++) {
        freeList(lists[i]);
    }

    return 0;
}