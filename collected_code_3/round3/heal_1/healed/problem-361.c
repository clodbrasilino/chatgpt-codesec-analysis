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
    
    if(newNode == NULL) {
        return NULL;
    }

    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

List* createList(Node* node) {
    List* newList = (List*)malloc(sizeof(List));
    
    if(newList == NULL) {
        return NULL;
    }

    newList->head = node;
    newList->next = NULL;

    return newList;
}

void removeEmptyLists(List** head) {
    List* temp = *head;
    List* prev = NULL;

    while(temp != NULL) {
        if(temp->head == NULL) {
            if(prev == NULL) {
                *head = temp->next;
                free(temp);
                temp = *head;
            } else {
                prev->next = temp->next;
                free(temp);
                temp = prev->next;
            }
        } else {
            prev = temp;
            temp = temp->next;
        }
    }
}

int main() {
    Node* node1 = createNode(1);
    Node* node2 = createNode(2);
    Node* node3 = NULL;

    if(node1 == NULL || node2 == NULL) {
        return -1;
    }

    List* list1 = createList(node1);
    List* list2 = createList(node2);
    List* list3 = createList(node3);

    if(list1 == NULL || list2 == NULL || list3 == NULL) {
        return -1;
    }

    list1->next = list2;
    list2->next = list3;

    removeEmptyLists(&list1);
    
    return 0;
}