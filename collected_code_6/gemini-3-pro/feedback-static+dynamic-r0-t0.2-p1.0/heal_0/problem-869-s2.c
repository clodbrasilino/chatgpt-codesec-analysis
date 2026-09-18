#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    struct List* next;
} List;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

List* createList(Node* head) {
    List* newList = (List*)malloc(sizeof(List));
    if (!newList) {
        exit(EXIT_FAILURE);
    }
    newList->head = head;
    newList->next = NULL;
    return newList;
}

void freeNodeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

void freeList(List* head) {
    List* current = head;
    while (current != NULL) {
        List* temp = current;
        current = current->next;
        freeNodeList(temp->head);
        free(temp);
    }
}

int isListInRange(Node* head, int min, int max) {
    Node* current = head;
    while (current != NULL) {
        if (current->data < min || current->data > max) {
            return 0;
        }
        current = current->next;
    }
    return 1;
}

List* removeSublistsOutsideRange(List* head, int min, int max) {
    List* current = head;
    List* prev = NULL;
    List* newHead = head;

    while (current != NULL) {
        if (!isListInRange(current->head, min, max)) {
            List* temp = current;
            if (prev == NULL) {
                newHead = current->next;
            } else {
                prev->next = current->next;
            }
            current = current->next;
            freeNodeList(temp->head);
            free(temp);
        } else {
            prev = current;
            current = current->next;
        }
    }
    return newHead;
}

void printList(List* head) {
    List* currentList = head;
    while (currentList != NULL) {
        Node* currentNode = currentList->head;
        printf("[");
        while (currentNode != NULL) {
            printf("%d", currentNode->data);
            if (currentNode->next != NULL) {
                printf(", ");
            }
            currentNode = currentNode->next;
        }
        printf("]\n");
        currentList = currentList->next;
    }
}

int main() {
    Node* n1 = createNode(1);
    n1->next = createNode(2);
    n1->next->next = createNode(3);

    Node* n2 = createNode(4);
    n2->next = createNode(5);
    n2->next->next = createNode(6);

    Node* n3 = createNode(2);
    n3->next = createNode(3);
    n3->next->next = createNode(4);

    List* l1 = createList(n1);
    l1->next = createList(n2);
    l1->next->next = createList(n3);

    int min = 2;
    int max = 4;

    l1 = removeSublistsOutsideRange(l1, min, max);

    printList(l1);

    freeList(l1);

    return 0;
}