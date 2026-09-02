#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
} List;

void reverseList(List *list) {
    Node *prev = NULL, *current = list->head, *next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    list->head = prev;
}

void reverseLists(List **lists, int n) {
    for (int i = 0; i < n; ++i) {
        if (lists[i] != NULL) {
            reverseList(lists[i]);
        }
    }
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

List* createList() {
    List* newList = (List*)malloc(sizeof(List));
    newList->head = NULL;
    return newList;
}

void appendToList(List *list, int data) {
    Node* newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node* temp = list->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void printList(List *list) {
    Node* temp = list->head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void freeList(List *list) {
    Node* head = list->head;
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    free(list);
}

int main() {
    int numLists = 3;
    List *lists[3];
    lists[0] = createList();
    lists[1] = createList();
    lists[2] = createList();

    appendToList(lists[0], 1);
    appendToList(lists[0], 2);
    appendToList(lists[0], 3);

    appendToList(lists[1], 4);
    appendToList(lists[1], 5);

    appendToList(lists[2], 6);
    appendToList(lists[2], 7);
    appendToList(lists[2], 8);
    appendToList(lists[2], 9);

    printf("Original lists:\n");
    for (int i = 0; i < numLists; ++i) {
        printf("List %d: ", i + 1);
        printList(lists[i]);
    }

    reverseLists(lists, numLists);

    printf("\nReversed lists:\n");
    for (int i = 0; i < numLists; ++i) {
        printf("List %d: ", i + 1);
        printList(lists[i]);
    }

    for (int i = 0; i < numLists; ++i) {
        freeList(lists[i]);
    }

    return 0;
}