#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL)
       return NULL;

    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void flattenList(Node* head) {
    Node* current = head;
    while(current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
}

Node* append(Node* head, Node* nodeToAppend) {
    if(head == NULL)
       return NULL;

    Node* current = head;
    while(current->next != NULL) {
        current = current->next;
    }
    current->next = nodeToAppend;
    return head;
}

int main() {
    Node* head = createNode(1);
    if(head == NULL)
       return 1;
   
    Node* second = createNode(2);
    if(second == NULL)
       return 1;

    Node* third = createNode(3);
    if(third == NULL)
       return 1;

    Node* fourth = createNode(4);
    if(fourth == NULL)
       return 1;

    Node* fifth = createNode(5);
    if(fifth == NULL)
       return 1;

    head->next = second;
    second->next = third;
    third->next = fourth;
    fourth->next = fifth;

    flattenList(head);

    return 0;
}