#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

void reverseList(List *list) {
    Node *prev = NULL;
    Node *current = list->head;
    Node *next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    list->head = prev;
}

void reverseLists(List *lists, int count) {
    for (int i = 0; i < count; ++i) {
        reverseList(&lists[i]);
    }
}

Node* createNode(int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

List* createList() {
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) {
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    return list;
}

void addNode(List *list, int value) {
    Node *newNode = createNode(value);
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node *temp = list->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void printList(List *list) {
    Node *temp = list->head;
    while (temp != NULL) {
        printf("%d -> ", temp->value);
        temp = temp->next;
    }
    printf("NULL\n");
}

void freeList(List *list) {
    Node *current = list->head;
    Node *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

int main() {
    List *lists[3];
    lists[0] = createList();
    lists[1] = createList();
    lists[2] = createList();

    addNode(lists[0], 1);
    addNode(lists[0], 2);
    addNode(lists[0], 3);

    addNode(lists[1], 4);
    addNode(lists[1], 5);

    addNode(lists[2], 6);
    addNode(lists[2], 7);
    addNode(lists[2], 8);
    addNode(lists[2], 9);

    printf("Original Lists:\n");
    for (int i = 0; i < 3; ++i) {
        printList(lists[i]);
    }

    reverseLists(lists, 3);

    printf("Reversed Lists:\n");
    for (int i = 0; i < 3; ++i) {
        printList(lists[i]);
    }

    for (int i = 0; i < 3; ++i) {
        freeList(lists[i]);
    }

    return 0;
}