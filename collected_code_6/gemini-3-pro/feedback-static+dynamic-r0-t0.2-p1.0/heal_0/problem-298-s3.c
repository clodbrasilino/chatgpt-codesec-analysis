#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct NestedList {
    Node* head;
    struct NestedList* next;
} NestedList;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

NestedList* createNestedList() {
    NestedList* newList = (NestedList*)malloc(sizeof(NestedList));
    if (!newList) {
        exit(EXIT_FAILURE);
    }
    newList->head = NULL;
    newList->next = NULL;
    return newList;
}

void appendNode(Node** head, int data) {
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

void appendNestedList(NestedList** head, Node* listHead) {
    NestedList* newList = createNestedList();
    newList->head = listHead;
    if (!*head) {
        *head = newList;
        return;
    }
    NestedList* temp = *head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newList;
}

bool isPresent(Node* list, int data) {
    Node* temp = list;
    while (temp) {
        if (temp->data == data) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void findCommonElements(NestedList* nested, Node* targetList) {
    NestedList* currentNested = nested;
    while (currentNested) {
        Node* currentNode = currentNested->head;
        while (currentNode) {
            if (isPresent(targetList, currentNode->data)) {
                printf("%d ", currentNode->data);
            }
            currentNode = currentNode->next;
        }
        currentNested = currentNested->next;
    }
    printf("\n");
}

void freeList(Node* head) {
    Node* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void freeNestedList(NestedList* head) {
    NestedList* temp;
    while (head) {
        temp = head;
        head = head->next;
        freeList(temp->head);
        free(temp);
    }
}

int main() {
    Node* targetList = NULL;
    appendNode(&targetList, 2);
    appendNode(&targetList, 4);
    appendNode(&targetList, 6);
    appendNode(&targetList, 8);

    NestedList* nestedList = NULL;
    
    Node* subList1 = NULL;
    appendNode(&subList1, 1);
    appendNode(&subList1, 2);
    appendNode(&subList1, 3);
    appendNestedList(&nestedList, subList1);

    Node* subList2 = NULL;
    appendNode(&subList2, 4);
    appendNode(&subList2, 5);
    appendNode(&subList2, 6);
    appendNestedList(&nestedList, subList2);

    findCommonElements(nestedList, targetList);

    freeList(targetList);
    freeNestedList(nestedList);

    return 0;
}