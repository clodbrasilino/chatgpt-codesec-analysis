#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    if(newNode == NULL){
        printf("Memory could not be allocated");
        exit(0);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Node* replaceLastElement(Node* list, Node* newList) {
    if(!list) return newList;

    Node* temp = list;
    while(temp->next && temp->next->next != NULL) {
        temp = temp->next;
    }

    if(temp->next != NULL) {
        free(temp->next);
        temp->next = newList;
    }
    return list;
}

int main() {
    Node* list1 = createNode(1);
    list1->next = createNode(2);

    Node* list2 = createNode(3);
    list2->next = createNode(4);

    list1 = replaceLastElement(list1, list2);
    Node* temp = list1;
    while(temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    // free the memory
    while(list1) {
        Node *next = list1->next;
        free(list1);
        list1 = next;
    }
    return 0;
}