#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct ListArray {
    Node** lists;
    int count;
} ListArray;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void appendNode(Node** head, int data) {
    if (!head) return;
    Node* newNode = createNode(data);
    if (!*head) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void freeList(Node* head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

void freeListArray(ListArray* la) {
    if (!la) return;
    if (la->lists) {
        for (int i = 0; i < la->count; i++) {
            freeList(la->lists[i]);
        }
        free(la->lists);
    }
    free(la);
}

ListArray* splitList(Node* head, int n) {
    if (n <= 0) return NULL;

    ListArray* la = (ListArray*)malloc(sizeof(ListArray));
    if (!la) {
        exit(EXIT_FAILURE);
    }
    la->lists = NULL;
    la->count = 0;

    if (!head) {
        return la;
    }

    int length = 0;
    Node* temp = head;
    while (temp) {
        length++;
        temp = temp->next;
    }

    int numLists = (length + n - 1) / n;
    la->lists = (Node**)calloc(numLists, sizeof(Node*));
    if (!la->lists) {
        free(la);
        exit(EXIT_FAILURE);
    }
    la->count = numLists;

    temp = head;
    for (int i = 0; i < numLists; i++) {
        Node* currentListHead = NULL;
        Node* currentListTail = NULL;
        for (int j = 0; j < n && temp; j++) {
            Node* newNode = createNode(temp->data);
            if (!currentListHead) {
                currentListHead = newNode;
                currentListTail = newNode;
            } else {
                currentListTail->next = newNode;
                currentListTail = newNode;
            }
            temp = temp->next;
        }
        la->lists[i] = currentListHead;
    }

    return la;
}

void printList(Node* head) {
    Node* temp = head;
    while (temp) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main(void) {
    Node* head = NULL;
    for (int i = 1; i <= 10; i++) {
        appendNode(&head, i);
    }

    int n = 3;
    ListArray* splitLists = splitList(head, n);

    if (splitLists) {
        for (int i = 0; i < splitLists->count; i++) {
            printf("List %d: ", i + 1);
            printList(splitLists->lists[i]);
        }
        freeListArray(splitLists);
    }

    freeList(head);
    return 0;
}