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
    if (newNode == NULL) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

List* createList(Node* node) {
    List* newList = (List*)malloc(sizeof(List));
    if (newList == NULL) {
        return NULL;
    }
    newList->head = node;
    newList->next = NULL;
    return newList;
}

List* removeEmptyLists(List* head) {
    List* temp = head;
    List* prev = NULL;

    while(temp != NULL) {
        if(temp->head == NULL) {
            if(prev == NULL) {
                head = temp->next;
            } else {
                prev->next = temp->next;
            }
            List* nextTemp = temp->next;
            free(temp);
            temp = nextTemp;
        } else {
            prev = temp;
            temp = temp->next;
        }
    }
    return head;
}

int main() {
    Node* node1 = createNode(1);
    if(node1 == NULL) return 1;
    Node* node2 = createNode(2);
    if(node2 == NULL) return 1;

    List* list1 = createList(node1);
    if(list1 == NULL) return 1;
    List* list2 = createList(node2);
    if(list2 == NULL) return 1;
    List* list3 = createList(NULL);

    list1->next = list2;
    list2->next = list3;

    List* head = removeEmptyLists(list1);

    while(head != NULL) {
        if(head->head != NULL) {
            printf("%d ", head->head->data);
        }
        head = head->next;
    }

    return 0;
}