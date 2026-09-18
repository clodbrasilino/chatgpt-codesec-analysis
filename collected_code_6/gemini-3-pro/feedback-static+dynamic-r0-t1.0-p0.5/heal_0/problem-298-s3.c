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

void appendNestedList(NestedList** head, Node* listHead) {
    if (!head) return;
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

bool isPresent(Node* head, int data) {
    Node* temp = head;
    while (temp) {
        if (temp->data == data) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

Node* findCommonElements(NestedList* nestedList, Node* targetList) {
    if (!nestedList || !targetList) return NULL;
    
    Node* resultHead = NULL;
    NestedList* currentNested = nestedList;
    
    while (currentNested) {
        Node* currentElement = currentNested->head;
        while (currentElement) {
            if (isPresent(targetList, currentElement->data) && !isPresent(resultHead, currentElement->data)) {
                appendNode(&resultHead, currentElement->data);
            }
            currentElement = currentElement->next;
        }
        currentNested = currentNested->next;
    }
    
    return resultHead;
}

void freeList(Node* head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

void freeNestedList(NestedList* head) {
    while (head) {
        NestedList* temp = head;
        head = head->next;
        freeList(temp->head);
        free(temp);
    }
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
    Node* targetList = NULL;
    appendNode(&targetList, 2);
    appendNode(&targetList, 4);
    appendNode(&targetList, 6);
    appendNode(&targetList, 8);

    Node* list1 = NULL;
    appendNode(&list1, 1);
    appendNode(&list1, 2);
    appendNode(&list1, 3);

    Node* list2 = NULL;
    appendNode(&list2, 4);
    appendNode(&list2, 5);
    appendNode(&list2, 6);

    NestedList* nestedList = NULL;
    appendNestedList(&nestedList, list1);
    appendNestedList(&nestedList, list2);

    Node* commonElements = findCommonElements(nestedList, targetList);

    printList(commonElements);

    freeList(targetList);
    freeNestedList(nestedList);
    freeList(commonElements);

    return 0;
}