#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL) {
        printf("Error creating a new node.\n");
        exit(0);
    }
    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

Node* mergeFirstLast(Node* list1, Node* list2) {
    Node* result = NULL;
    Node* temp = list2;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    result = createNode(list1->data + temp->data);
    return result;
}

int main() {
    Node* list1 = createNode(5);
    list1->next = createNode(10);
    list1->next->next = createNode(15);

    Node* list2 = createNode(20);
    list2->next = createNode(25);
    list2->next->next = createNode(30);

    Node* result = mergeFirstLast(list1, list2);
    printf("Merged first and last elements: %d\n", result->data);

    free(list1->next->next);
    free(list1->next);
    free(list1);
    free(list2->next->next);
    free(list2->next);
    free(list2);
    free(result);

    return 0;
}