#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void freeList(Node* head) {
    /* Possible weaknesses found:
     *  The scope of the variable 'tmp' can be reduced. [variableScope]
     */
    Node* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

bool containsSublist(Node* list, Node* sublist) {
    if (sublist == NULL) {
        return true;
    }
    if (list == NULL) {
        return false;
    }

    Node* currentList = list;
    
    while (currentList != NULL) {
        Node* ptr1 = currentList;
        Node* ptr2 = sublist;
        
        while (ptr1 != NULL && ptr2 != NULL && ptr1->data == ptr2->data) {
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
        
        if (ptr2 == NULL) {
            return true;
        }
        
        currentList = currentList->next;
    }
    
    return false;
}

int main(void) {
    Node* list = createNode(1);
    if (!list) return 1;
    list->next = createNode(2);
    if (!list->next) { freeList(list); return 1; }
    list->next->next = createNode(3);
    if (!list->next->next) { freeList(list); return 1; }
    list->next->next->next = createNode(4);
    if (!list->next->next->next) { freeList(list); return 1; }
    
    Node* sublist = createNode(2);
    if (!sublist) { freeList(list); return 1; }
    sublist->next = createNode(3);
    if (!sublist->next) { freeList(list); freeList(sublist); return 1; }
    
    bool result = containsSublist(list, sublist);
    
    if (result) {
        printf("List contains the sublist.\n");
    } else {
        printf("List does not contain the sublist.\n");
    }
    
    freeList(list);
    freeList(sublist);
    
    return 0;
}