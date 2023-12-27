#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* divideLists(Node* list1, Node* list2) {
    Node* quotient = NULL;
    Node* currentQ = NULL;
    
    while (list1 != NULL && list2 != NULL) {
        Node* newNode = (Node*) malloc(sizeof(Node));
        
        if(newNode == NULL) {
            return NULL; // Memory allocation failed.
        }
        
        newNode->next = NULL;

        if (list1->data < list2->data) {
            newNode->data = 0;
            list1 = list1->next;
        } else {
            newNode->data = 1;
            list1 = list1->next;
            list2 = list2->next;
        }

        if (quotient == NULL) {
            quotient = newNode;
            currentQ = newNode;
        } else {
            currentQ->next = newNode;
            currentQ = currentQ->next;
        }
    }

    return quotient;
}

int main() {
    Node* list1 = (Node*) malloc(sizeof(Node));
    Node* list2 = (Node*) malloc(sizeof(Node));
    
    if(list1 == NULL || list2 == NULL)
        exit(EXIT_FAILURE); // Memory allocation failed. 

    list1->data = 10;
    list2->data = 5;

    list1->next = (Node*) malloc(sizeof(Node));
    list2->next = (Node*) malloc(sizeof(Node));
    
    if(list1->next == NULL || list2->next == NULL)
        exit(EXIT_FAILURE); // Memory allocation failed. 

    list1->next->data = 20;
    list2->next->data = 10;
    list1->next->next = NULL;
    list2->next->next = NULL;
    
    Node* result = divideLists(list1, list2);
    
    while (result != NULL) {
        printf("%d ", result->data);
        result = result->next;
    }
    
    return 0;
}