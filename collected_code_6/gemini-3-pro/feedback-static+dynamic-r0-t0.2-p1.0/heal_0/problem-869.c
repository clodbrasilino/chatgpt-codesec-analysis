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

void freeListOfLists(List* head) {
    List* current = head;
    while (current != NULL) {
        List* temp = current;
        current = current->next;
        freeNodeList(temp->head);
        free(temp);
    }
}

int getListLength(Node* head) {
    int length = 0;
    Node* current = head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

List* removeSublistsOutsideRange(List* head, int minLen, int maxLen) {
    List* current = head;
    List* prev = NULL;
    List* newHead = head;

    while (current != NULL) {
        int len = getListLength(current->head);
        if (len < minLen || len > maxLen) {
            List* temp = current;
            if (prev == NULL) {
                newHead = current->next;
                current = current->next;
            } else {
                prev->next = current->next;
                current = current->next;
            }
            freeNodeList(temp->head);
            free(temp);
        } else {
            prev = current;
            current = current->next;
        }
    }
    return newHead;
}

void printListOfLists(List* head) {
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

int main(void) {
    Node* n1 = createNode(1);
    n1->next = createNode(2);
    
    Node* n2 = createNode(3);
    n2->next = createNode(4);
    n2->next->next = createNode(5);
    
    Node* n3 = createNode(6);
    
    List* l1 = createList(n1);
    List* l2 = createList(n2);
    List* l3 = createList(n3);
    
    l1->next = l2;
    l2->next = l3;
    
    List* filteredList = removeSublistsOutsideRange(l1, 2, 2);
    
    printListOfLists(filteredList);
    
    freeListOfLists(filteredList);
    
    return 0;
}